/*
 * @brief Power Management Unit(PMU) example using the ROM API
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
/* GPIO pin for PINIT input */
/* Board specific definitions */
#if defined(BOARD_NXP_LPCXPRESSO_812) || defined(BOARD_LPC812MAX) || defined(BOARD_NXP_LPCXPRESSO_824)
#define GPIO_PININT		4
#else
#warning "No GPIO assigned for this example"
#endif

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void blinkLEDCount(uint32_t count)
{
	volatile uint32_t index;

	/* Perform the requested number of times */
	for (; count; --count) {
		Board_LED_Toggle(0);
		for (index = 0; index < 100000; ++index) {}	/* delay */
		Board_LED_Toggle(0);
		for (index = 0; index < 100000; ++index) {}	/* delay */
	}
}

/**
 * @brief	Handle interrupt from PININT0
 * @return	Nothing
 */
void PININT0_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH0);
}

/**
 * @brief	Main routine for Power example
 * @return	Function should not exit
 */
int main(void)
{
	uint32_t cmdData[3];
	uint32_t response;
	uint32_t sleepFlags;

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	/* Set main clock to the IRC since the PLL will be disabled by default upon wakeup */
	Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_IRC);
	SystemCoreClockUpdate();

	/* get the sleep flags and clear them in HW */
	sleepFlags = Chip_PMU_GetSleepFlags(LPC_PMU);
	Chip_PMU_ClearSleepFlags(LPC_PMU, PMU_PCON_DPDFLAG);

	/* Only do this if restarting from a COLD reset */
	if (!(sleepFlags & PMU_PCON_DPDFLAG)) {

		/* Set default state of LED to ON */    //LED0=RED=PIO0_12, LED0=RED=PIO0_16, LED0=RED=PIO0_27,
		Board_LED_Set(0, true);
	}

	/* Enable the clock to the Switch Matrix */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);

	/* Make sure fixed pin function is disabled and assign something safe to it */
	Chip_SWM_DisableFixedPin(SWM_FIXED_ADC11);
	Chip_SWM_MovablePinAssign(SWM_SCT_IN1_I, GPIO_PININT);

	/* Configure channel 0 interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_SetPinModeEdge(LPC_PININT, PININTCH0);
	Chip_PININT_EnableIntLow(LPC_PININT, PININTCH0);

	/* Configure interrupt channel 0 for the GPIO pin in SysCon block */
	Chip_SYSCTL_SetPinInterrupt(0, GPIO_PININT);

	/* Configure channel 0 as wake up interrupt in SysCon block */
	Chip_SYSCTL_EnablePINTWakeup(0);

	/* Configure GPIO pin as input pin */
	Chip_GPIO_PinSetDIR(LPC_GPIO_PORT, 0, GPIO_PININT, 1);

	/* Enable interrupt in the NVIC */
	NVIC_EnableIRQ(PININT0_IRQn);

//	/* Set power state (Not required but shown for reference) */
//	cmdData[0] = 12;
//	cmdData[1] = PWR_EFFICIENCY;
//	cmdData[2] = 12;
//	__disable_irq();
//	LPC_ROM_API->pPWRD->set_power(cmdData, &response);
//	__enable_irq();

//	/* if failure response don't proceed */
//	if (response) {
//		while (1) {
//			blinkLEDCount(2);
//		}
//	}

	/* Configure ARM to only allow enabled IRQ's to wake us up */
	SCB->SCR &= ~(SCB_SCR_SEVONPEND_Msk);

	/* Only do this if restarting from a COLD reset */
	if (!(sleepFlags & PMU_PCON_DPDFLAG)) {
		/* Inidicate all ready to begin sleep sequence */
		{
			volatile uint32_t count;
			for (count = 0; count < 1000000; ++count) {}			//about 2s
		}
		Board_LED_Set(0, false);
	}
	else {
		Board_LED_Set(0, true);
		while(1);				// if from deep power down, while with LED0 ON
	}
	
	
	
	

		/* Indicate entering sleep */
		blinkLEDCount(2);
		/* Clear deep sleep bit to enable regular sleep, and finally enter sleep via wfi */
		Chip_PMU_SleepState(LPC_PMU);

		/* Indicate entering deep sleep */
		blinkLEDCount(4);
		/* By default, IRC, IRC_OUT, FLASH and BOD systems are enabled when waking from deep sleep.
		   All other systems are powered off. */
		/* Set deep sleep bit to enable regular sleep */
		Chip_PMU_DeepSleepState(LPC_PMU);

		/* Indicate entering power down state */
		blinkLEDCount(8);
		Chip_PMU_PowerDownState(LPC_PMU);

		/* Indicate entering deep power down.  When we wake from here, MPU will act as if
		   it were reset. */
		blinkLEDCount(16);
		Chip_PMU_DeepPowerDownState(LPC_PMU);
		
		
//		while (1);
		
}
