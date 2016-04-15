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
#define FLASH_ADDR_TEST (LPC_FLASH_BASE + 0x6000)
#define FLASH_SECTOR_SIZE (1024)
#define RAM_BUFFER_SIZE (512)
static __attribute__((section(".RAM_1K"))) uint32_t ram_buffer[RAM_BUFFER_SIZE];

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

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */


/**
 * @brief	main routine for blinky example
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t uid, pid, bootrom_version;
	uint32_t flash_start_sector, flash_end_sector, i;
	uint8_t ret;

	SystemCoreClockUpdate();
	Board_Init();

	Board_LED_Set(0, false);


	/* Chip General information */
	/* Chip PID */
	//	0x00008241 = LPC824M201JHI33
	//	0x00008221 = LPC822M101JHI33
	//	0x00008242 = LPC824M201JDH20
	//	0x00008222 = LPC822M101JDH20

	Chip_IAP_ReadUID(&uid);
	pid = Chip_IAP_ReadPID();
	bootrom_version = Chip_IAP_ReadBootCode();	
	sprintf(debug_output, "CHIP UID: 0x%x, PID: 0x%x, Bootloader Ver: 0x%x\r\n", 
			uid, pid, bootrom_version);
	Board_UARTPutSTR(debug_output);

	/*Check flash functionalities */
	flash_start_sector = (FLASH_ADDR_TEST - LPC_FLASH_BASE)/FLASH_SECTOR_SIZE;
	flash_end_sector = flash_start_sector + 1;

	ret = Chip_IAP_BlankCheckSector(flash_start_sector, flash_end_sector);
	if (ret == 0) {
		sprintf(debug_output, "Before Programing: FLASH is blank\r\n");
	} else {
		sprintf(debug_output, "Before Programing: FLASH is NOT blank\r\n");
	}
	Board_UARTPutSTR(debug_output);

	for(i = 0;i < RAM_BUFFER_SIZE; i++) {
		ram_buffer[i] = i%256;
	}

	ret = Chip_IAP_PreSectorForReadWrite(flash_start_sector, flash_end_sector);
	if (ret == IAP_CMD_SUCCESS) {
		ret = Chip_IAP_EraseSector(flash_start_sector, flash_end_sector);
		if (ret == IAP_CMD_SUCCESS) {
			ret = Chip_IAP_PreSectorForReadWrite(flash_start_sector, flash_end_sector);			
			ret = Chip_IAP_CopyRamToFlash(FLASH_ADDR_TEST - LPC_FLASH_BASE,
				ram_buffer, RAM_BUFFER_SIZE);
			if(ret == IAP_CMD_SUCCESS) {
				ret = Chip_IAP_BlankCheckSector(flash_start_sector, flash_end_sector);
				if (ret == 0) {
					sprintf(debug_output, "After Programing: FLASH is blank\r\n");
				} else {
					sprintf(debug_output, "After Programing: FLASH is NOT blank\r\n");
				}
				Board_UARTPutSTR(debug_output);				
				ret = Chip_IAP_Compare(FLASH_ADDR_TEST - LPC_FLASH_BASE,
					(uint32_t)&ram_buffer, RAM_BUFFER_SIZE);
				if (ret == 0)
					sprintf(debug_output, "Compare result same!!\r\n");
				else
					sprintf(debug_output, "Compare result differ!!\r\n");
				Board_UARTPutSTR(debug_output);				
			}
		}
	}
	
	
	/* Loop forever */
	while (1) {
		__WFI();
	}
}
