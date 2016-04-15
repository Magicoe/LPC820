/*
 * @brief General Purpose Input/Output example
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
#define LED1_PIN 12
#define LED2_PIN 27
#define LED3_PIN 16

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
static void delay(void)
{
	uint32_t i, j;
	for(i=0; i<1000; i++)
	for(j=0; j<1000; j++);
}

/**
 * @brief	Main program body
 * @return	Does not return
 */
int main(void) 
{
	uint32_t GPIOCONFIG = ( (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN) );
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	/* Set port 0 pins 27,13,17,16 to the output direction*/
	Chip_GPIO_PortSetDIR(LPC_GPIO_PORT, 0, GPIOCONFIG, 1);

	/* Set GPIO port mask value to make sure only port 0
	   pins 0-3 (0-1 on 824) are active during state change */
	Chip_GPIO_PortSetState(LPC_GPIO_PORT, 0, GPIOCONFIG);

	/* All work happens in the systick interrupt handler */
	while (1) {
		Chip_GPIO_PortSetOutLow(LPC_GPIO_PORT, 0, GPIOCONFIG);
		delay();
		Chip_GPIO_PortSetOutHigh(LPC_GPIO_PORT, 0, GPIOCONFIG);
		delay();		
	}
}

// end file
