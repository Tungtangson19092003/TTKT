/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_it_user.c
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MMF
* Tool-Chain   : CCRL
* Description  : This file implements device driver for IT module.
* Creation Date: 2017/5/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_it.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_lcd.h"
#include "r_cg_12adc.h"
#include "r_cg_iica.h"
#include "r_cg_sau.h"
#include "r_cg_tau.h"
#include "user_macrodrive.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_it_interrupt(vect=INTIT)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern Run_Mode g_RunMode;
extern uint8_t g_DataBuffer[];
extern uint16_t g_SampleData[64][2];
extern uint16_t g_Index;
extern uint8_t g_TempIndex;
extern uint16_t g_TempData[17];
extern Run_Mode g_RunMode;
extern int8_t g_DiffValue[64];
extern uint8_t g_SampleDataIndex;
extern uint8_t g_MeasureFlag;
extern uint8_t g_I2CError;
uint8_t g_SampleCounter;
uint16_t g_SleeveNormalCounter;

static uint16_t g_DisplayShuffle;       /* The counter is used to change LED and LCD display */
static uint16_t g_DisplayCloseCounter;  /* The counter is used to close LED and LCD display */
extern uint8_t g_PulseData;
extern uint8_t g_HighPressureData;
extern uint8_t g_LowPressureData;
extern void timer_isr(void);    /* defined by timer.h */
extern void RefreshLCD(uint16_t data);
extern uint8_t Press_Read(uint8_t Length,uint8_t *DataPoint);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_it_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_it_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
	int8_t t_Diver[16];
	uint8_t i;
	int8_t t_min_data;
	timer_isr();
	
	if( g_RunMode == Display_mode )
	{
		/* Close LCD display after 50s */
		if( g_DisplayCloseCounter++ > 5000)
		{
			R_LCD_Stop();
			g_MeasureFlag = 0;
			g_DisplayCloseCounter = 0;
			g_RunMode = Init_mode;	
		}
	}
	
	g_SampleCounter++;	/* Sample the pressure data every 20ms */
	if( ( g_SampleCounter == 2 ) && ( g_MeasureFlag == 1) )
	{
		g_SampleCounter = 0;
		g_I2CError = Press_Read(2,g_DataBuffer);
		if( g_I2CError == 0 )
		{
			g_RunMode = Error_mode;		/* IIC communication error*/
		}
		switch( g_RunMode )
		{
			case AddPressure_mode:
				g_TempData[g_TempIndex] = g_DataBuffer[0];
				g_TempData[g_TempIndex] = ( g_TempData[g_TempIndex] << 8 ) + g_DataBuffer[1];
				g_TempIndex++;
				if( g_TempIndex > 2)
				{
					/* Get the average pressure every 3 times */
					g_TempIndex = 0;
					g_TempData[0] = (g_TempData[0] + g_TempData[1] + g_TempData[2])/3;
					if( g_TempData[0] > MAX_PRESS ) /* Stop add pressure if the pressure > 160mmHg */
					{
						g_RunMode = WaitStable_mode;
						R_TAU0_Channel6_Stop();
						TO0 = 0x0000;	        	/* Output low level after stop PWM */
					}
					else if(g_SleeveNormalCounter++ > 4000)
					{
						g_SleeveNormalCounter = 0;
						g_RunMode = Error_mode;		/* Add pressure error*/
					}
				}
			break;	
			case WaitStable_mode:
				if ( g_TempIndex++ >= 10 )     		/* Wait for pressure stably */
				{
					g_TempIndex = 0;
					g_Index = 0;
					g_RunMode = Deflate_mode;
				}				
			break;
			case Deflate_mode:		
			    if( g_Index >= 1024 )				/* Capture 1024 pressure data about 20s */
				{
					g_Index = 0;
					g_SampleDataIndex = 0;
					VALVE_CTRL = 0;
					R_TAU0_Channel0_Stop();
					g_RunMode = Calculate_mode;
					return;
				}
				
				g_TempData[g_TempIndex] = g_DataBuffer[0];
				g_TempData[g_TempIndex] = ( g_TempData[g_TempIndex] << 8 ) + g_DataBuffer[1];
				/* Calculate the max pulse data every 16 sampling data */
				if( ( g_Index%16 == 0 ) && (g_Index != 0) )
				{
					for( i = 0; i < 16; i++)
					{
						t_Diver[i] = (int8_t)( g_TempData[i] - g_TempData[i+1] );
					}
					t_min_data = t_Diver[0];
					for( i = 0; i < 16; i++)
					{
		    			if( t_Diver[i] < t_min_data )
							t_min_data = t_Diver[i];			
					}
					g_DiffValue[g_SampleDataIndex] = t_min_data;
					for( i = 0; i < 16; i++)
					{
						if( t_Diver[i] == t_min_data )
							break;
					}
					g_SampleData[g_SampleDataIndex][0] = 16*( ( g_Index/16 ) - 1) + i;
					g_SampleData[g_SampleDataIndex][1] = g_TempData[i];
					g_SampleDataIndex++;
					g_TempData[0] = g_TempData[16];
					g_TempIndex = 0;
				}
				g_Index++;
				g_TempIndex++;
				break;			
			case Display_mode:
				g_DisplayShuffle++;		/* Change display every 4s */
				if( g_DisplayShuffle < 200 )
				{
					RefreshLCD(g_HighPressureData);
					LED0 = ON;
					LED1 = OFF;
					LED2 = OFF;
				}
				if( ( g_DisplayShuffle < 400 ) &&( g_DisplayShuffle >= 200 ) )
				{
					RefreshLCD(g_LowPressureData);
					LED0 = OFF;
					LED1 = ON;
					LED2 = OFF;
				}
				if( ( g_DisplayShuffle < 600 ) &&( g_DisplayShuffle >= 400 ) )
				{
					RefreshLCD(g_PulseData);
					LED0 = OFF;
					LED1 = OFF;
					LED2 = ON;
				}
				if( g_DisplayShuffle > 600)
				{
					g_DisplayShuffle = 0;
				}
				
			break;
		}
	}
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
