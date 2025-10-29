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
* File Name    : r_cg_port.c
* Version      : Code Generator for RL78/L1A V1.00.01.01 [11 Nov 2016]
* Device(s)    : R5F11MMF
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Port module.
* Creation Date: 2017/5/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    PFSEG0 = _40_PFSEG06_SEG | _20_PFSEG05_SEG | _10_PFSEG04_SEG | _80_PFSEG0_DEFAULT_VALUE;
    PFSEG1 = _80_PFSEG15_SEG | _40_PFSEG14_SEG | _20_PFSEG13_SEG | _10_PFSEG12_SEG | _0F_PFSEG1_DEFAULT_VALUE;
    PFSEG2 = _40_PFSEG22_SEG | _00_PFSEG21_PORT | _10_PFSEG20_SEG | _08_PFSEG19_SEG | _00_PFSEG18_PORT | 
             _00_PFSEG17_PORT | _00_PFSEG16_PORT | _80_PFSEG2_DEFAULT_VALUE;
    PFSEG3 = _20_PFSEG29_SEG | _08_PFSEG27_SEG | _04_PFSEG26_SEG | _02_PFSEG25_SEG | _D1_PFSEG3_DEFAULT_VALUE;
    PFSEG4 = _80_PFSEG39_SEG | _40_PFSEG38_SEG | _20_PFSEG37_SEG | _10_PFSEG36_SEG | _08_PFSEG35_SEG | 
             _04_PFSEG34_SEG | _02_PFSEG33_SEG | _01_PFSEG4_DEFAULT_VALUE;
    PFSEG5 = _10_PFSEG44_SEG | _08_PFSEG43_SEG | _01_PFSEG40_SEG | _06_PFSEG5_DEFAULT_VALUE;
    PM3 = _18_PM3_DEFAULT_VALUE | _80_PMn7_MODE_INPUT | _40_PMn6_MODE_INPUT | _20_PMn5_MODE_INPUT | 
          _04_PMn2_MODE_INPUT | _00_PMn1_MODE_OUTPUT | _01_PMn0_MODE_INPUT;
    PM7 = _80_PMn7_MODE_INPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT | 
          _08_PMn3_MODE_INPUT | _04_PMn2_MODE_INPUT | _02_PMn1_MODE_INPUT | _01_PMn0_MODE_INPUT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
