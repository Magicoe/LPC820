LPC8xx ADC Example
==================

Example Description
-------------------
The LPC82x ADC example shows how to use the ADC to perform a sequence of
conversions and monitor a threshold crossing. Sampling is started by manually
initiating the ADC sequence in the system tick interrupt. When the ADC sample
sequence is complete, it generates an interrupt. During ADC sequence conversion,
an interrupt will also be generated if the sample crosses the threshold value.
Converted ADC values are displayed via the DEBUG UART.

Special Connection Requirements
-------------------------------
Board [NXP_LPCXPRESSO_824]:
Please put FRDM mini shield on the LPCXpresso824 board.
Adjust potentiometer on the FRDM min shield and ADC values will be displayed via DEBUG UART.

��DEMO��ʾ����ADC�Ĺ���(����ADC��sequence��threshold)����system tick���жϽ��д���ADC�Ĳ�����
��ADC����sequence��ɻ����һ��ADC�жϣ���������Ľ��������ֵҲ������жϡ�
�����Ľ����ͨ��DEBUG UART�ڴ�ӡ������


��FRDM mini shield���Ӳ���LPCXpresso824���ӵ�ardiuno�ӿڣ����س����λ��
����FRDM mini shield�����ϵĵ�λ�������Թ۲�DEBUG UART�ڵĴ�ӡ�����


