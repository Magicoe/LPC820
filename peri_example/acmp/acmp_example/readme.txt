Analog Comparator Example
=========================

Example Description
-------------------
The ACMP example demonstrates the analog comparator.

This example configures the comparator positive input to the  potentiometer on the
LPCXpresso base-board (FRDM mini shield). 
The negative input is connected to the internal band-gap
reference voltage. The output of the comparator is used to drive an LED.
The comparator threshold is configured to generate an interrupt.

When the potentiometer is adjusted right and left, the voltage to the positive 
side of the comparator is changed. When the voltage crosses the negative
comparator input, a CMP_IRQ is fired. Based on the voltage reference in relation
to the band-gap, the LED state will change.

Special Connection Requirements
-------------------------------
Board [NXP_LPCXPRESSO_824]:
Please put FRDM mini shield on the LPCXpresso824 board.
Adjust potentiometer on the FRDM min shield and find LED D1 will blink.

此DEMO演示的是比较器的功能，比较器的正极(P0_6)连接上电位器的分压端，
负极连接到内部分压端(0.9V)。比较器的输出产生中断，驱动LED的亮灭。


把FRDM mini shield板子插入LPCXpresso824板子的ardiuno接口，下载程序后复位，
调节FRDM mini shield板子上的电位器，可以观察到LED D1的亮或者灭。