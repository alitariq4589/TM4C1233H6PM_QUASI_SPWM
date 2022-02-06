# TM4C1233H6PM_QUASI_SPWM

**_>>>This project and its source codes are available for educational purposes and not for commercial uses unless agreed/permitted. The distribution of this software after modifications on educational grounds must be mentioned explicitly. Anyone using this project completely or partially can and will be subjected to proper legal actions according to international or regional laws, rules and regulations<<<_**

TM4C123 has 5 general purpose timers (GPTM) which we can use for implementation of this code. The pins connections are as follows:

Connect PF_2 to PF_4 and PF_3 to PB_1 through external jumpers.
PB_1 and PF_4 are the PWM production pins. Also connect them to oscilloscope to see the output.

Quasi SPWM is conventional SPWM but with dead-bands on both sides of the SPWM for inverters. As, it is Quasi, so there are total of two waves produced from the microcontroller, one for positive on-time and one for negative on-time. Dead-band is added for safety of switching devices (either mosfet or IGBT). This complete algorithm is interrupts-driven.
