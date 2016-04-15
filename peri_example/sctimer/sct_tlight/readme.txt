State Configurable Timer (SCT) traffic light Example
==========================================

Example Description
-------------------
This example, uses the SCT to implement traffic light demo.Three SCT output signals (SCT_OUT0 - SCT_OUT2) are connected to chip external pins to drive board led. User should connect P0_13 to Yellow Led, P0_27 to green led and P0_17 to red led.
The SCT is configured using LPCxpresso Red State which is a graphic finite state development tool. 

Special Connection Requirements
-------------------------------

Board [NXP_LPCXPRESSO_824]:

Use FRDM mini shiled borad, which has LD2, LD3 and LD4 connect to SCT out signals. 

Build procedures:
Visit the LPCOpen Quick start guide at
[http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides]
to get started building LPCOpen projects.
