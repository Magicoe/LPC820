Cyclic Redundancy Check (CRC) Generator Example
===============================================

Example Description
-------------------
The CRC example demonstrates using the CRC engine for 8-bit, 16-bit, and
32-bit CRC computation. The CRC engine will continuously run via CRC
computations and verify the CRC checksum. The system tick is used to
occasionally introduce CRC errors into the expected data. The board LED
will turn on for an error and turn off for no errors.

Special Connection Requirements
-------------------------------
Board [NXP_LPCXPRESSO_824]:
There are no special connection requirements for this example.


使用CRC引擎计算8位、16位和32位的CRC计算。CRC引擎持续的进行CRC计算并且校验CRC的结果。
system tick产生一个10Hz的时钟，每隔一个时钟，把CRC的结果result[2]进行减1(即修改为错误的值)。
每个循环计算的result[0] ~ result[4]的值再进行CRC32计算，计算出的结果gencrc与期盼的结果进行
比较，正确LED灭，不正确LED亮。
