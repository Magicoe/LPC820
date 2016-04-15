LPC82x DMA Memory to Memory Transfer Example
============================================

Example Description
-------------------
This example shows how to setup and use the DMA controller for a limited
software triggered memory to memory transfer. Because of the limited burst
transfer size of the DMA (1024 transfers max) and limited burst size, DMA
M2M operations are somewhat specialized, but they do have a good performance
boost over memcpy() and memmove() functions. They would work best for
smaller transfers.

Time measurement for performance is in milliSeconds. Lower values indicate
higher data transfer performance. A time 50% smaller than another time would
mean the same operation was about 2x faster. Times are provided for similar
memmove(), memcpy(), and DMA data move operations.

The example also includes a test enable definition (XFERTEST) that will
also perform data testing when it is defined.

Note: This example uses the debug UART.
Open UART terminal program to view the results of the transfer.

Special Connection Requirements
-------------------------------

Board [NXP_LPCXPRESSO_824]:
There are no special connection requirements for this example.

此demo展示了DMA控制器的建立，软件触发memory到memory的数据传输。
DMA的数据传输与memcpy()/memmove()功能进行了性能方面的比较。设置了一个
毫秒定时器对各种数据传输的计时，计时结果通过DEBUG UART打印出来。