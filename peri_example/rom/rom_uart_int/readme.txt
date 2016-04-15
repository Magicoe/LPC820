UART API in ROM (USART API ROM) Interrupt Example
=================================================

Example Description
-------------------
The UART_ROM example demonstrates using the USART API ROM functions
in interrupt mode for terminated data input and output.

An example ringbuffer capability is also provided using the
uart_get_line() and uart_put_line() functions in interrupt mode.

Special connection requirements
-------------------------------
Board [NXP_LPCXPRESSO_812]:
See @ref LPCOPEN_8XX_BOARD_LPCXPRESSO_812 for information on how to
setup the UART port hardware with this example..

Board [NXP_812_MAX]:
See LPC812_max-UART.txt for UART configuration details.

Board [NXP_LPCXPRESSO_824]:
See LPC824_xpresso-UART.txt for UART configuration details.

NOTE: When connecting to the base board make sure P3 Pin4 [RST] pin of the
LPCXpresso board is *NOT* connected to the base board for the debugger to work.

Build procedures
----------------
Visit the <a href="http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides">LPCOpen quickstart guides</a>
to get started building LPCOpen projects.
