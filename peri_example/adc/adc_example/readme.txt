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

此DEMO演示的是ADC的功能(包括ADC的sequence和threshold)。在system tick的中断进行处罚ADC的采样，
当ADC采样sequence完成会产生一个ADC中断，如果采样的结果触发阀值也会产生中断。
采样的结果会通过DEBUG UART口打印出来。


把FRDM mini shield板子插入LPCXpresso824板子的ardiuno接口，下载程序后复位，
调节FRDM mini shield板子上的电位器，可以观察DEBUG UART口的打印结果。


