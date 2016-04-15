/*
 * @brief State Configurable Timer (SCT) example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
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

/*****************************************************************************
 * Public functions
 ****************************************************************************/

void SCT_Init(void)
{
    LPC_SCT->CONFIG |= 0x1;                            // unified timer
                                                  
    LPC_SCT->MATCH[0].U    = SystemCoreClock/10;       // match 0 @ 100 msec
    LPC_SCT->MATCHREL[0].U = SystemCoreClock/10;

    LPC_SCT->EV[0].STATE = 0x00000001;                  // ev 0 happens in state 0
    LPC_SCT->EV[0].CTRL  = (0 << 0)  |                  // related to match 0
                               (1 << 12) |              // match condition only
                               (1 << 14) |              // STATEV is new state
                               (1 << 15);               // STATEV[15] = 1
    LPC_SCT->EV[1].STATE = 0x00000002;                  // ev 1 happens in state 1
    LPC_SCT->EV[1].CTRL  = (0 << 0)  |                  // related to match 0
                               (1 << 12) |              // match condition only
                               (1 << 14) |              // STATEV is new state
                               (0 << 15);               // STATEV[15] = 0

    LPC_SCT->OUT[0].SET = (1 << 0);                    // event 0 sets SCT_OUT_0
    LPC_SCT->OUT[0].CLR = (1 << 1);                    // event 1 clears SCT_OUT_0
    LPC_SCT->LIMIT_L = 0x0003;                         // event 0 and 1 are limits

}


/**
 * @brief	Application main program
 * @return	Nothing (This function will not return)
 */
int main(void)
{
	/* Generic Initialization */
 	SystemCoreClockUpdate();

	/* Custom Initialization */
	
	/*Assign SCT_out to board LED pin*/
	Chip_SWM_MovablePinAssign(SWM_SCT_OUT0_O, 27);		// assign SCTOUT_0 to P0_17 RED_LED
	
	/* Initialize the SCT clock and reset the SCT */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SCT);
	Chip_SYSCTL_PeriphReset(RESET_SCT);

	/*Initialize SCT*/
	SCT_Init();
	
	/* Start the SCT counter by clearing Halt_L in the SCT control register */
	Chip_SCT_ClearControl(LPC_SCT, SCT_CTRL_HALT_L);

	while (1) {
		__WFI();
	}
}
