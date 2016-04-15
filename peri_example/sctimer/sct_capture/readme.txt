State Configurable Timer (SCT) Capture Example
==========================================

Example Description
-------------------
This example, uses the SCT input0 falling edge to generate event0 which will cause capture of the counter into the capture0 register and generate an interrupt. The program will then read the captured counter value and print out to debug uart1. Developer can use mbed virtual serial port to read the printing value.

Special Connection Requirements
-------------------------------

Board [NXP_LPCXPRESSO_824]:
SCT input0 connects to J2-D5 (P0_28)
Use FRDM mini shiled borad, which has key K4 connect to P0_28, or connect exteranl Key to this signal. 

Build procedures:
Visit the LPCOpen Quick start guide at
[http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides]
to get started building LPCOpen projects.
