#ifndef NVIC_H
#define NVIC_H

#include "stm32l432xx.h"

void NVIC_EnableInterrupt(IRQn_Type IRQn);
void NVIC_DisableInterrupt(IRQn_Type IRQn);
void NVIC_SetInterruptPriority(IRQn_Type IRQn, uint8_t priority);

#endif