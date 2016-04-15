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


ʹ��CRC�������8λ��16λ��32λ��CRC���㡣CRC��������Ľ���CRC���㲢��У��CRC�Ľ����
system tick����һ��10Hz��ʱ�ӣ�ÿ��һ��ʱ�ӣ���CRC�Ľ��result[2]���м�1(���޸�Ϊ�����ֵ)��
ÿ��ѭ�������result[0] ~ result[4]��ֵ�ٽ���CRC32���㣬������Ľ��gencrc�����εĽ������
�Ƚϣ���ȷLED�𣬲���ȷLED����
