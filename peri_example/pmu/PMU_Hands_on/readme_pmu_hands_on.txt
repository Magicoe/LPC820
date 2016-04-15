Power API Example
=================

Example Description
-------------------
The Power example demonstrates using the various power down modes.  The example puts 
the MCU into each of the power states (SLEEP, DEEP_SLEEP, POWER_DOWN, and DEEP_POWER_DOWN).

This example configures the pin interrupt channel 0 as falling edge 
wake up interrupt. The interrupt channel 0 is connected to GPIO pin 
PIO0-4 in GPIO block. The example will then flash the LED according to the following table.

Sleep:  		2 flashes
Deep sleep: 	4 flashes
Power down:		8 flashes
Deep power down:16 flashes

To wake up from sleep mode, press the Wake button.  

Note:  When waking up from deep power-down the MPU will resume at the reset vector.  When resuming
the PMU_PCON_DPDFLAG flag will be set which allows startup to detect cold start vs wake from 
deep power-down.

Special Connection Requirements
-------------------------------
Board [NXP_LPCXPRESSO_812]:
There are no buttons on this board so it becomes interesting to wake the processor.
First, a pull-up resistor (100K) must be added to PIO0_4.
Next, a jumper must be used to bring PIO0_4 low. The easiest way to do this is to use J7,
the UART header. Short J7 pin-5 (TX) to J7 pin-1 (GND).

Board [NXP_812_MAX]:
Similar to the NXP_LPCXPRESSO_812, there is no button connected to PIO0_4.
So again, it becomes interesting to wake the processor.
First, a pull-up resistor (100K) must be added to PIO0_4.
Next, a jumper must be used to bring PIO0_4 low. The easiest way to do this is to use J2,
the Arduino digital header. Short J2 pin-7 (TX) to J1 pin-4 (GND).
Note that the silk screen calls this pin 1.

Board [NXP_LPCXPRESSO_824]:
There are no special connection requirements for this example.
On NXP LPCXpresso_824 board use SW1 (Wake) button to activate the interrupt.

Build procedures:
Visit the <a href="http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides">LPCOpen quickstart guides</a>
to get started building LPCOpen projects.
