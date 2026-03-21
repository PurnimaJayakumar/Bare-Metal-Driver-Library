#include "nvic.h"

void NVIC_EnableInterrupt(IRQn_Type IRQn)
{
    NVIC_EnableIRQ(IRQn);
}

void NVIC_DisableInterrupt(IRQn_Type IRQn)
{
    NVIC_DisableIRQ(IRQn);
}

void NVIC_SetInterruptPriority(IRQn_Type IRQn, uint8_t priority)
{
    NVIC_SetPriority(IRQn, priority);
}