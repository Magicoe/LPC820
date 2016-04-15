/*
 * @brief Switch Matrix hands on example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2016
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void I2C_PinMux_Init(void) 
{ 
#if 0
    /* Enable SWM clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);

    /* I2C1_SDA to PIO0_11 */
    LPC_SWM->PINASSIGN[9] &= 0xffff00ffUL;   
    LPC_SWM->PINASSIGN[9] |= 0x00000b00UL;
 
    /* I2C1_SCL to PIO0_10*/
    LPC_SWM->PINASSIGN[9] &= 0xff00ffffUL;
    LPC_SWM->PINASSIGN[9] |= 0x000a0000UL; 

    /* Disable SWM clock to save power */
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<7);
#else
	/* Enable the clock to the Switch Matrix */
	Chip_SWM_Init();
	/* Connect the I2C_SDA1 and I2C_SCL1 signals to port pins(P0.10, P0.11) */
	Chip_SWM_MovablePinAssign(SWM_I2C1_SDA_IO, 10);
	Chip_SWM_MovablePinAssign(SWM_I2C1_SCL_IO, 11);
	/* Disable the clock to the Switch Matrix to save power */
	Chip_SWM_Deinit();
#endif
// Enable interrupt, etc. after switching functions
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/


/**
 * @brief	Main program body
 * @return	Does not return
 */
int main(void) {

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	
	#if defined(BOARD_NXP_LPCXPRESSO_824)
	I2C_PinMux_Init();
	#endif

	/* All work happens in the systick interrupt handler */
	while (1) {
		__WFI();
	}
}
