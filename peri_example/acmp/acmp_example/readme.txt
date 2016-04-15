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

��DEMO��ʾ���ǱȽ����Ĺ��ܣ��Ƚ���������(P0_6)�����ϵ�λ���ķ�ѹ�ˣ�
�������ӵ��ڲ���ѹ��(0.9V)���Ƚ�������������жϣ�����LED������


��FRDM mini shield���Ӳ���LPCXpresso824���ӵ�ardiuno�ӿڣ����س����λ��
����FRDM mini shield�����ϵĵ�λ�������Թ۲쵽LED D1����������