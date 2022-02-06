# TM4C1233H6PM_QUASI_SPWM
Quasi SPWM is conventional SPWM but with dead-bands on both sides of the SPWM for inverters. As, it is Quasi, so there are total of two waves produced from the microcontroller, one for positive on-time and one for negative on-time. Dead-band is added for safety of switching devices (either mosfet or IGBT). This complete algorithm is interrupts-driven.
