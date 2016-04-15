/*
 * @brief IAP example using system IAP functions
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
#include <stdio.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
/*****************************************************************************
 * Private functions
 ****************************************************************************/
static char debug_output[256];
 
/*****************************************************************************
 * Public functions
 ****************************************************************************/
const static uint32_t FLASH_SIGNATURE_START_ADDR = 0x1000;
const static uint32_t FLASH_SIGNATURE_END_ADDR = 0x4000;
/**
 * @brief	main routine for blinky example
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t flash_signature = 0;

	SystemCoreClockUpdate();
	Board_Init();

	Board_LED_Set(0, false);

	Chip_FMC_ComputeSignature(FLASH_SIGNATURE_START_ADDR, FLASH_SIGNATURE_END_ADDR);

	while(Chip_FMC_IsSignatureBusy());

	flash_signature = Chip_FMC_GetSignature(0);

	sprintf(debug_output, "FLASH Signature: 0x%x, startAddr = 0x%x, endAddr = 0x%x", flash_signature, FLASH_SIGNATURE_START_ADDR, FLASH_SIGNATURE_END_ADDR);
	DEBUGSTR(debug_output);

	/* Loop forever */
	while (1) {
		__WFI();
	}
}
