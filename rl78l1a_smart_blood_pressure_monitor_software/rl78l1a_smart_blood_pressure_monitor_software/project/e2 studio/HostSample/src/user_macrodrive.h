/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : user_macrodrive.h
* Version      : V1.00 [30 May 2017]
* Device(s)    : R5F1176A
* Tool-Chain   : CC-RL V1.04.00
* Description  : This file implements header file for macro define.
* Creation Date: 30/05/2017
***********************************************************************************************************************/

#ifndef _MACRO_DEF_
#define _MACRO_DEF_

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define VALVE_CTRL      P3_bit.no1              /* Solenoid valve control port */
#define PUMP_CTRL       P7_bit.no7              /* Air pump control port */
#define LED0            P7_bit.no4              /* LED0 control port */
#define LED1            P7_bit.no5              /* LED1 control port */
#define LED2            P7_bit.no6              /* LED2 control port */
#define SCL_INPUT 		(PM6_bit.no0 = 1)    	/* Set "scl" as input port */
#define SCL_OUTPUT 		(PM6_bit.no0 = 0)   	/* Set "scl" as output port */
#define SCL_LOW 		(P6_bit.no0 = 0)        /* Set "scl" output "0" */
#define SCL_HIGH 		(P6_bit.no0 = 1)        /* Set "scl" output "1" */
#define SCL_INDATA 		(P6_bit.no0)           	/* Read "scl" */
#define SDA_INPUT 		(PM6_bit.no1 = 1)       /* Set "sda" as input port */
#define SDA_OUTPUT 		(PM6_bit.no1 = 0)      	/* Set "sda" as output port */
#define SDA_LOW 		(P6_bit.no1 = 0)        /* Set "sda" output "0" */
#define SDA_HIGH 		(P6_bit.no1 = 1)        /* Set "sda" output "1" */
#define SDA_INDATA 		(P6_bit.no1)           	/* Read "sda" */
#define PORT_INPUT      1U
#define PORT_OUT        0U
#define HIGH            1U
#define LOW             0U
#define ON              1U
#define OFF             0U
#define ACK 			0U
#define NACK 			1U
#define IIC_BUS_ADDRESS 0x51U                   /* IIC device address */
#define KS				5                       /* Systolic pressure parameter */
#define KD				7                       /* Diastolic pressure parameter */
#define MAX_PRESS		8000                    /* Max pressure setting */

#define LCD_NUM1            (&SEG33)
#define LCD_NUM2            (&SEG35)
#define LCD_NUM3            (&SEG37)
#define LCD_NUM4            (&SEG39)
typedef enum {
              Init_mode = 0,
			  Idle_mode = 1,
			  AddPressure_mode = 2,
			  WaitStable_mode = 3,
              Deflate_mode = 4,
			  Calculate_mode = 5,
			  Display_mode = 6,
			  Error_mode = 7
             }Run_Mode;
#endif