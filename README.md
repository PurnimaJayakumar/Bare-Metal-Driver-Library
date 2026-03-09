# Bare-Metal-Driver-Library
1. Commented out HAL includes in main.h (Line 30)
2. Commented out HAL_init() from main.c (Line 73)
3. Leftout files:
stm32l4xx_hal_conf.h
stm32l4xx_hal_msp.c
stm32l4xx_it.h
stm32l4xx_it.c
ClockConfig made into register level in main.c
