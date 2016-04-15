LPC82x UART using DMA example
=============================

Example Description
-------------------
This examples shows how to use the DMA controller to handle servicing
of UART transmit and receive operations to offload the MCU and reduce
interrupt processing.<br>

UART transmit operations have a known transmit size and are queued to the
DMA controller via descriptors setup for the transfer. Descriptors are
only queued to the DMA controller when data is waiting to be sent.
This specific implementation can queue multiple UART buffers with a single
DMA interrupt per UART buffer sent. This example doesn't used linked
DMA descriptors.<br>

UART receive operations have a fixed list of descriptors and buffer sizes.
The DMA controller will generate a DMA interrupt for UART receive only when
a full buffer of data has been received. Once this buffer is received, it
is sent back out via UART transmit via DMA.<br>

Special Connection Requirements
-------------------------------
Board [NXP_LPCXPRESSO_812]:
There are no special connection requirements for this example.

Board [NXP_812_MAX]:
There are no special connection requirements for this example.

Board [NXP_LPCXPRESSO_824]:
Connect the board to a base board. The output will appear at USB-mini port X3.
Make sure that the jumpers on J7 are configured correctly.
Or, connect TX, RX and GND from J2 [Arduino Digital Header] to an FTDI Cable.
LPC824            FTDI cable
 GND: J1-4         black
 RX:  J2-8 (D0)    orange
 TX:  J2-7 (D1)    yellow

To use the VCOM UART, enable the USE_VCOM define and move SJ9 to pins 2-3.


Build procedures
----------------
Visit the
["http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"]
LPCOpen quickstart guides to get started building LPCOpen projects.

