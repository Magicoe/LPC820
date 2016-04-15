/*
 * @brief General Purpose Input/Output hands on 2
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
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
#define LED1_PIN		12
#define LED2_PIN		16
#define LED3_PIN		27

#define KEY1_PIN		4

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/


/**
 * @brief	Main program body
 * @return	Does not return
 */
int main(void) {

	uint32_t LED_GPIO_CONFIG = ( (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN) );
	uint32_t KEY_GPIO_CONFIG = ( (1 << KEY1_PIN) );
	
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	
	#if defined(BOARD_NXP_LPCXPRESSO_824)
	/* Enable clock to switch matrix so we can configure the matrix */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	/* 824 needs the fixed pin ACMP2 pin disabled to use pin as gpio */
	Chip_SWM_DisableFixedPin(SWM_FIXED_CLKIN);
	
	/* Turn clock to switch matrix back off to save power */
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
	#endif
	
	/* Led pin Set port 0 pins 27,13,17,16 to the output direction*/
	Chip_GPIO_PortSetDIR(LPC_GPIO_PORT, 0, LED_GPIO_CONFIG, 1);
	
	/* Key pin Set port 0 pins 19,12,18,28 to the input direction*/
	Chip_GPIO_PortSetDIR(LPC_GPIO_PORT, 0, KEY_GPIO_CONFIG, 0);


	/* All work happens in the systick interrupt handler */
	while (1) {
		// key1 button
		if( Chip_GPIO_PinGetState(LPC_GPIO_PORT, 0, KEY1_PIN) == 0 ) {
			Chip_GPIO_PortSetOutLow(LPC_GPIO_PORT, 0, (1 << LED3_PIN));
		}
		else {
			Chip_GPIO_PortSetOutHigh(LPC_GPIO_PORT, 0, (1 << LED3_PIN));
		}
	}
}

// end file
