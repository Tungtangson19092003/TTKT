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
* File Name    : r_cg_main.c
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MMF
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 2017/5/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
#include "r_cg_it.h"
#include "r_cg_12adc.h"
#include "r_cg_sau.h"
#include "r_cg_lcd.h"
#include "r_cg_intp.h"
/* Start user code for include. Do not edit comment generated here */
#include "arch.h"
#include "rscip_api.h"
#include "rl78l1adef.h"
#include "timer.h"
#include "rble_app.h"
#include "rble_host.h"
#include "uart.h"
#include "user_macrodrive.h"
#include "float.h"
#include "string.h"
#include "stdio.h"
#include "math.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
uint8_t data_received[2];			/* Data buffer for BLE receive */
uint8_t g_MeasureFlag;				/* Measure flag, g_MeasureFlag = 1: in measure status, g_MeasureFlag = 0: not in measure status */
uint8_t g_DataBuffer[2];			/* Data buffer for honeywell pressure sensor */
uint16_t g_SampleData[64][2];		/* Useful sample data after get the max difference every 16 original sample data */
uint16_t g_Index;					/* Original sample data index: 0 ~ 1023*/
uint8_t g_TempIndex;				/* Temp index for calculate the max difference every 16 original sample data */
uint16_t g_TempData[17];			/* Temp data every 16 original sample data */
int8_t g_DiffValue[64];				/* The difference value for useful sample data */
uint8_t g_SampleDataIndex;			/* Useful sample data index: 0 ~ 63*/
uint8_t g_PulseData;				/* Pulse data */
uint8_t g_HighPressureData;			/* Systolic pressure data */
uint8_t g_LowPressureData;			/* Diastolic pressure data */
uint8_t g_BatteryLevel;				/* Battery level data */
uint8_t g_I2CError;					/* IIC communication error flag */
uint8_t g_DisplayData[4];           /* Variable for data display */
const uint16_t g_NumberData[12] = {0x0e0b,0x0600,0x0c07,0x0e05,0x060c,0x0a0d, /* "0'~"9", "" and "E" */
                                   0x0a0f,0x0e00,0x0e0f,0x0e0d,0x0000,0x080f};

Run_Mode g_RunMode = Init_mode;		/* Run mode define */
void QueuePulseData(void);
void CalculatePressure(void);
uint8_t DataAbs(uint8_t data);
uint8_t CalculatePulse(void);
_Bool SPNoiseFilter(uint8_t Index);
_Bool DPNoiseFilter(uint8_t Index);
void LCDView(void);
void LCDErrorInfo(uint8_t data);
void RefreshLCD(uint16_t data);
void Delayus(uint16_t time);
void Delayms(uint16_t time);
void I2C_Init(void);
uint8_t Press_Read(uint8_t Length,uint8_t *DataPoint);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

static void R_MAIN_UserInit(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    RPECTL = 0x80;
	/* Initialize IIC function */
	I2C_Init();
	/* Enable INTP0 */
	R_INTC0_Start();
    /* Enable UART for communication with RL78/G1D */
    R_UART0_Start(); 
    /* Initialize rBLE Timer */
    if ( RBLE_OK == RBLE_Init_Timer() )
    {
        /* Initialize Application */
        if ( TRUE == APP_Init() )
        {
            /* Main Loop(not break) */
            while(1)
            {
                /* Sequence Management Section */
                APP_Run();
                rBLE_Run();
				switch( g_RunMode )
				{
					case Init_mode:
						VALVE_CTRL = LOW;		// Open valve(deflate rapidly)
						LED0 = OFF;
						LED1 = OFF;
						LED2 = OFF;
						g_TempIndex = 0;
				        g_Index = 0;
						g_RunMode = Idle_mode;
						
					break;
					
					case Idle_mode:
						R_12ADC_Start();
					break;
					
					case Calculate_mode:
						CalculatePressure();
						QueuePulseData();
						g_PulseData = CalculatePulse();
						if( ( g_PulseData < 40) || (g_PulseData > 180) || (g_HighPressureData > 250) || (g_LowPressureData < 30) )
							g_RunMode = Error_mode;
						else
							g_RunMode = Display_mode;
					break;
					
					case Error_mode:
						VALVE_CTRL = 0;
						R_TAU0_Channel6_Stop();
						TO0 = 0x0000;	        	/* Output low level after stop PWM */
						if( ( g_PulseData < 40) || (g_PulseData > 180) )
							LCDErrorInfo(3);		/* E3: pulse error */
						else if( (g_HighPressureData > 250) || (g_LowPressureData < 40))
							LCDErrorInfo(2);		/* E2: blood pressure error */
						else 
							LCDErrorInfo(1);		/* E1: other error */
					break;
					
					default:
					break;
				}
                /* MCU Stop Management Section */
                GLOBAL_INT_DISABLE();
                if( rBLE_Is_Idle() && APP_Is_Idle() && RSCIP_Can_Sleep() && rBLE_Timer_Can_Sleep() && ( g_RunMode == Idle_mode) )
                {
                    #if (!SERIAL_U_DIV_2WIRE)
                    if(R_UART0_Snooze() == MD_OK)
                    {
                        WFI();
                    }
                    #else
                    __halt();
                    #endif
                }
                GLOBAL_INT_RESTORE();
            }

            /* Finalize rBLE Host */
            /* rBLE_Exit(); */
        }
    }
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/******************************************************************************
* Function Name : DataAbs
* Description   : This function implements making absolute value of data.
* Arguments     : uint8_t
* Return Value  : uint8_t
******************************************************************************/
uint8_t DataAbs(uint8_t data)
{
	if( data < 128 )
		return data;
	else
	    return( 256 - data );		
}

/******************************************************************************
* Function Name : CalculatePressure
* Description   : This function implements calculating blood pressure value.
* Arguments     : none
* Return Value  : none
******************************************************************************/
void CalculatePressure(void)
{
	uint8_t i,j;
	int8_t t_mini_data;
	float t_pressure,t_pressure_m;
	t_mini_data = g_DiffValue[0];
	for(i = 0; i < 64; i++)
	{
		if( t_mini_data >= g_DiffValue[i] )
		{
			t_mini_data = g_DiffValue[i];
		}
	}
	/* Get the max pulse point*/
	for(i = 0; i < 64; i++)
	{
		if( g_DiffValue[i] == t_mini_data )
			break;
	}
	/* Calculate systolic pressure */
	t_pressure_m =  DataAbs(g_DiffValue[i]);
	for(j = (i - 1); j > 0; j--)
	{
		if( g_DiffValue[j] < 0 )
		{
			t_pressure = DataAbs(g_DiffValue[j]);	
			t_pressure *= 10;
			if( ( ( t_pressure/t_pressure_m ) < KS) && ( SPNoiseFilter(j) ) )
			{
			 	break;
			}
		}
	}
	
	t_pressure = g_SampleData[j][1] - 1638;
	t_pressure = ( t_pressure * 5 )/13107;
	g_HighPressureData = (uint8_t)( (t_pressure*6895)/133.322 );
	/* Calculate diastolic pressure */
	for(j = (i + 1); j < 64; j++)
	{
		if( g_DiffValue[j] < 0 )
		{
			t_pressure = DataAbs(g_DiffValue[j]);	
			t_pressure *= 10;
			if( ( ( t_pressure/t_pressure_m ) < KD) && ( DPNoiseFilter(j) ) )
			 	break;
		}
	}
	
	t_pressure = g_SampleData[j][1] - 1638;
	t_pressure = ( t_pressure * 5 )/13107;
	g_LowPressureData = (uint8_t)( (t_pressure*6895)/133.322 );
}

/******************************************************************************
* Function Name : SPNoiseFilter
* Description   : This function is used to filter the noise data of systolic pressure.
* Arguments     : uint8_t
* Return Value  : _Bool
******************************************************************************/
_Bool SPNoiseFilter(uint8_t Index)
{
	uint8_t i;
	for( i = ( Index-1 ); i > 0; i--)
	{
		if( g_DiffValue[i] < g_DiffValue[Index] )
		{
			return(0);
		}
	}
	return(1);
}
/******************************************************************************
* Function Name : DPNoiseFilter
* Description   : This function is used to filter the noise data of dilational pressure.
* Arguments     : uint8_t
* Return Value  : _Bool
******************************************************************************/
_Bool DPNoiseFilter(uint8_t Index)
{
	uint8_t i;
	for( i = ( Index+1 ); i < 64; i++)
	{
		if( g_DiffValue[i] < g_DiffValue[Index] )
		{
			return(0);
		}
	}
	return(1);
}
/******************************************************************************
* Function Name : QueuePulseData
* Description   : This function is used to queue the pulse data from min to max.
* Arguments     : uint8_t
* Return Value  : _Bool
******************************************************************************/
void QueuePulseData(void)
{
	uint8_t i,j,k;
	int8_t t_mini_data;
	
	for(i = 0; i < 64; i++)
	{
		t_mini_data = g_DiffValue[i];
		for(j = i; j < 64; j++)
		{
			if( t_mini_data >= g_DiffValue[j] )
			{
				t_mini_data = g_DiffValue[j];
			}
		}
		for(k = i; k < 64; k++)
		{
			if( g_DiffValue[k] == t_mini_data )
			{
				g_DiffValue[i] = k;
				if( k != i )
				{
					g_DiffValue[k] = 127;
				}
				break;
			}
		}
	}
}
/******************************************************************************
* Function Name : QueuePulseData
* Description   : This function calculate the pulse data.
* Arguments     : none
* Return Value  : uint8_t
******************************************************************************/
uint8_t CalculatePulse(void)
{
	uint8_t i,j,t_PulseData;
	uint16_t t_temp_data;
	uint16_t t_PulseArray[10];
	uint8_t t_DiffPulse[9];
	for(i = 0; i < 10; i++)
	{
		t_PulseArray[i] = g_SampleData[g_DiffValue[i]][0];
	}	
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < (10-i); j++ )
		{
			if( t_PulseArray[j] > t_PulseArray[j+1])
			{
				t_temp_data = t_PulseArray[j];
				t_PulseArray[j] = t_PulseArray[j+1];
				t_PulseArray[j+1] = t_temp_data;
			}
		}
	}
	t_temp_data = 0;
	j = 0;
	for(i = 0; i < 9; i++)
	{
		t_DiffPulse[i] = t_PulseArray[i+1] - t_PulseArray[i];
		if( ( t_DiffPulse[i] > 16 ) &&  ( t_DiffPulse[i] < 75 ) )
		{
			t_temp_data += t_DiffPulse[i];
			j++;
		}
	}
	
	t_PulseData = ( uint8_t )( t_temp_data / (uint16_t)j );
	t_temp_data = (uint16_t)t_PulseData * 2;    /*20ms*/
	t_PulseData = ( 6000/t_temp_data );         /*pulse/minute*/
	return(t_PulseData);
}

/******************************************************************************
* Function Name : LCDView
* Description   : This function implements Refreshing LCD module.
* Arguments     : none
* Return Value  : none
******************************************************************************/
void LCDView(void)
{
	R_LCD_Start();
    memcpy((void __near *)LCD_NUM1, &g_NumberData[0], 2);    /* Displays Num1 */
    memcpy((void __near *)LCD_NUM2, &g_NumberData[0], 2);    /* Displays Num2 */
    memcpy((void __near *)LCD_NUM3, &g_NumberData[0], 2);    /* Displays Num3 */
    memcpy((void __near *)LCD_NUM4, &g_NumberData[0], 2);    /* Displays Num4 */

}

/******************************************************************************
* Function Name : LCDErrorInfo
* Description   : This function implements error information LCD module.
* Arguments     : none
* Return Value  : none
******************************************************************************/
void LCDErrorInfo(uint8_t data)
{
    memcpy((void __near *)LCD_NUM1, &g_NumberData[11], 2);      /* Displays Num1 */
    memcpy((void __near *)LCD_NUM2, &g_NumberData[data], 2);    /* Displays Num2 */
    memcpy((void __near *)LCD_NUM3, &g_NumberData[10], 2);      /* Displays Num3 */
    memcpy((void __near *)LCD_NUM4, &g_NumberData[10], 2);      /* Displays Num4 */

}

/******************************************************************************
* Function Name : RefreshLCD
* Description   : This function implements Refreshing LCD module.
* Arguments     : data
* Return Value  : none
******************************************************************************/
void RefreshLCD(uint16_t data)
{
	g_DisplayData[0] = data / 1000;
	g_DisplayData[1] = data % 1000 / 100;
	g_DisplayData[2] = data % 100 / 10;
	g_DisplayData[3] = data % 10;
	if (g_DisplayData[0] == 0)
	{
		g_DisplayData[0] = 10;
		if (g_DisplayData[1] == 0)
			g_DisplayData[1] = 10;
	}
    memcpy((void __near *)LCD_NUM1, &g_NumberData[g_DisplayData[0]], 2);    /* Displays Num1 */
    memcpy((void __near *)LCD_NUM2, &g_NumberData[g_DisplayData[1]], 2);    /* Displays Num2 */
    memcpy((void __near *)LCD_NUM3, &g_NumberData[g_DisplayData[2]], 2);    /* Displays Num3 */
    memcpy((void __near *)LCD_NUM4, &g_NumberData[g_DisplayData[3]], 2);    /* Displays Num4 */
}

/******************************************************************************
* Function Name : Delayus
* Description   : This function implements Delayus function.
* Arguments     : uint16_t
* Return Value  : none
******************************************************************************/
void Delayus(uint16_t time)
{
    uint16_t i;
    for(i = 0; i < time; i++);
    {
	    __nop();
	    __nop();
    }
}

/******************************************************************************
* Function Name : Delayms
* Description   : This function implements Delayms function.
* Arguments     : uint16_t
* Return Value  : none
******************************************************************************/
void Delayms(uint16_t time)
{
    uint16_t i;
    for(i = 0; i < time; i++)
    {
        Delayus(200);
        Delayus(200);
        Delayus(200);
        Delayus(200);
        Delayus(200);
    }
}
 /******************************************************************************
* Function Name:I2C_Init
* Description : This function implements I2C_Init function.
* Arguments : none
* Return Value : none
******************************************************************************/
void I2C_Init(void)
{
    /* Initialize SCL and SDA ports */
    POM1 = 0;
    
    SCL_LOW;    
    SCL_OUTPUT;   
    
    SDA_LOW;   
    SDA_OUTPUT;    
         
    Delayus(5); /* Wait 2us */
}

/******************************************************************************
* Function Name:I2C_Start
* Description : This function implements I2C_Start function.
* Arguments : none
* Return Value : none
******************************************************************************/
void I2C_Start(void)
{   /* I2C start condition*/
    SDA_OUTPUT;
    SCL_LOW;
    Delayus(2);
    SDA_HIGH;
    Delayus(2);
    SCL_HIGH;
    Delayus(2); 
    SDA_LOW;      
    Delayus(2); 
    SCL_LOW;      
    Delayus(2); 
}

/******************************************************************************
* Function Name:I2C_Stop
* Description : This function implements I2C_Stop function.
* Arguments : none
* Return Value : none
******************************************************************************/
void I2C_Stop(void)
{   /* I2C stop condition*/
    SDA_LOW;
    SDA_OUTPUT; 
    Delayus(1);
    SDA_LOW;
    Delayus(2);
    SCL_HIGH;
    Delayus(2); 
    SDA_HIGH;  
    Delayus(2);
    SCL_LOW;
    Delayus(2);
}

/******************************************************************************
* Function Name:I2C_WriteByte
* Description : This function implements I2C_WriteByte function.
* Arguments : uint8_t
* Return Value : uint8_t
******************************************************************************/
uint8_t I2C_WriteByte(uint8_t dat)
{
    /*Write 1byte data to I2C device */
    uint8_t i,result; 
    SDA_OUTPUT;
    for(i = 0;i < 8; i++) 
    {
        SCL_LOW;
        if(dat & 0x80)        
        {
            SDA_HIGH;       
        }
        else
        {
            SDA_LOW;        
        }
                
        Delayus(1);
        SCL_HIGH;        
        dat <<= 1;       
        Delayus(2);  
        SCL_LOW;
        Delayus(1);
    }
    SDA_INPUT;
    Delayus(1);
    SCL_HIGH;       
    if(SDA_INDATA)
    {
        result = 0;     /* Write operation failed flag */    
    }
    else
    {
        result = 1;     /* Write operation success flag */   
    }           
    Delayus(2);
    SCL_LOW;
    return result;      
}

/******************************************************************************
* Function Name:I2C_ReadByte
* Description : This function implements I2C_ReadByte function.
* Arguments : uint8_t
* Return Value : uint8_t
******************************************************************************/
uint8_t I2C_ReadByte(uint8_t ack)
{   
    /* Read 1byte data from I2C device */
    uint8_t i,dat = 0;     
    SDA_INPUT; 
    for(i = 0;i < 8;i++)      
    {
        SCL_LOW;          
        Delayus(1);
        SCL_HIGH;
        dat <<= 1;       
        if(SDA_INDATA)
        {
            dat++;  
        }
        Delayus(2);
        SCL_LOW;
        Delayus(1);
    }
    SDA_OUTPUT;
    SCL_LOW;
    Delayus(1);
    if(ack == NACK)     
    {
        SDA_HIGH;   
    }
    else
    {
        SDA_LOW;        
    }
    SCL_HIGH;
    Delayus(2);
    SCL_LOW;
    Delayus(1);
    SDA_HIGH;
    return (dat);     
}

/******************************************************************************
* Function Name:Press_Read
* Description : This function implements read pressure data function.
* Arguments : uint16_t
* Return Value : none
******************************************************************************/
uint8_t Press_Read(uint8_t Length,uint8_t *DataPoint)
{
    /* Read 1 page data from I2C device */
    uint8_t i,flag;
    flag = FALSE;
    I2C_Start();                            
    flag = I2C_WriteByte(IIC_BUS_ADDRESS);     
    if (0 == flag)
    {
        I2C_Stop(); 
        return(0);
    }
   
    for(i = 0; i < Length; i++)
    {
        *DataPoint = I2C_ReadByte(ACK); 
		DataPoint++;
    }
    *DataPoint = I2C_ReadByte(NACK);
    I2C_Stop(); 
	return(1);
}  
/* End user code. Do not edit comment generated here */
