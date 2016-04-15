Hello World Example
===================

Example Description
-------------------
The Hello World example sends a "Hello World!" message out the virtual serial
port every 2 seconds.  The port is configured as 115200 N81.  The blue "USB com"
led will blink at this same rate as well.
 
Special connection requirements
-------------------------------
Board [NXP_LPCXPRESSO_812]:

Board [NXP_812_MAX]:
See LPC812_max-UART.txt for details on configuring the UART.

Board [NXP_LPCXPRESSO_824]:
To avoid interaction between serial console and debug channel configure and
connect to the vcom port prior to initiating a debug session.

Build procedures:
Visit the <a href="http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides">LPCOpen quickstart guides</a>
to get started building LPCOpen projects.
