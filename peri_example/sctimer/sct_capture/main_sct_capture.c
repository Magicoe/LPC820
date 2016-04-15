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

volatile uint32_t cap_flag = 0;

void SCT_Init(void)
{
    LPC_SCT->CONFIG |= 0x1;                            // unified timer
		
		LPC_SCT->REGMODE_U = 0x1;														//match0 operates as capture register
    LPC_SCT->CAPCTRL[0].U = 0x1;													//event 0 causes capture 0	                                              

    LPC_SCT->EV[0].STATE = 0x00000001;                  // ev 0 happens in state 0
    LPC_SCT->EV[0].CTRL  = (1 << 0)  |                  // related to match 0
															 (0 << 5) |							//select input
															 (0 << 6) |							//select sct_input0 
															 (2 << 10) |							//falling edge																
                               (2 << 12) |              // input condition only
                               (1 << 14) |              // STATEV is new state
                               (0 << 15);               // STATEV[15] = 0

}

void SCT_IRQHandler(void)
{
	cap_flag = 1;

	/* Clear the SCT Event 0 Interrupt */
	Chip_SCT_ClearEventFlag(LPC_SCT, SCT_EVT_0);
}

/**
 * @brief	Application main program
 * @return	Nothing (This function will not return)
 */
int main(void)
{
	/* Generic Initialization */
 	SystemCoreClockUpdate();
	
	Board_Init();
	
	/* Custom Initialization */
	

	/*Assign SCT_input to board key pin*/
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	Chip_SWM_MovablePinAssign(SWM_SCT_IN0_I, 28);		// assign SCT_INPUT0 to P0_28
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
	
	/* Initialize the SCT clock and reset the SCT */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SCT);
	Chip_SYSCTL_PeriphReset(RESET_SCT);
	Chip_INMUX_SetSCTInMux(LPC_INMUX, SCT_INMUX_0, SCT_INP_IN0);
	
	/*Initialize SCT*/
	SCT_Init();
	
	/* Enable flag to request an interrupt for Event 0 */
	Chip_SCT_EnableEventInt(LPC_SCT, SCT_EVT_0);

	/* Enable the interrupt for the SCT */
	NVIC_EnableIRQ(SCT_IRQn);
	
	/* Start the SCT counter by clearing Halt_L in the SCT control register */
	Chip_SCT_ClearControl(LPC_SCT, SCT_CTRL_HALT_L);

	while (1) {
		
		__WFI();
		
		if(cap_flag == 1)
		{
			DEBUGOUT("0x%X\r\n", LPC_SCT->CAP[0].U);
			cap_flag = 0;
		}		
					
	}
}
