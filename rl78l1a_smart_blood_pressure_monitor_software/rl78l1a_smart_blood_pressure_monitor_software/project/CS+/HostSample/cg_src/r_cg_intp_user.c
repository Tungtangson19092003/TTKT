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
* File Name    : r_cg_intp_user.c
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MMF
* Tool-Chain   : CCRL
* Description  : This file implements device driver for INTP module.
* Creation Date: 2017/5/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_intp.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_tau.h"
#include "r_cg_it.h"
#include "r_cg_lcd.h"
#include "user_macrodrive.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_intc0_interrupt(vect=INTP0)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern Run_Mode g_RunMode;
extern uint8_t g_MeasureFlag;
extern void LCDView(void);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_intc0_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_intc0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
	if( g_RunMode == Idle_mode)
	{
        VALVE_CTRL = HIGH;		// Close valve
        R_TAU0_Channel6_Start();
		R_LCD_Voltage_On();
		R_LCD_Start();
		g_RunMode = AddPressure_mode;
		g_MeasureFlag = 1;
		/* LCD initialize display */
		LCDView();
	}
	else
	{
		R_TAU0_Channel6_Stop();
		TO0 = 0x0000;	        // Output low level after stop PWM
		g_RunMode = Init_mode;
		R_LCD_Stop();
		g_MeasureFlag = 0;
	}
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
