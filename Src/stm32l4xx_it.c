#include "stm32l432xx.h"

// Weak callbacks
__attribute__((weak)) void TIM2_Callback(void) {}
__attribute__((weak)) void USART2_Callback(void) {}
__attribute__((weak)) void EXTI_Callback(void) {}

// TIM2 Interrupt Handler
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        TIM2_Callback();
    }
}

// USART2 Interrupt Handler
void USART2_IRQHandler(void)
{
    if (USART2->ISR & USART_ISR_RXNE)
    {
        USART2_Callback();
    }
}

// EXTI Line (example: line 13)
void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1 << 13))
    {
        EXTI->PR1 |= (1 << 13);
        EXTI_Callback();
    }
}