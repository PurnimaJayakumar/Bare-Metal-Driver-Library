#include "ti_mer.h"

/* BASIC TIMER CONFIGURATION */
void timer_basic_init(TIM_TypeDef *TIMx, uint16_t prescaler, uint16_t arr)
{
    /* Enable timer clock */
    if(TIMx == TIM2)
        RCC->APB1ENR |= (1<<0);
    else if(TIMx == TIM3)
        RCC->APB1ENR |= (1<<1);

    TIMx->PSC = prescaler;
    TIMx->ARR = arr;

    TIMx->CNT = 0;
}

/* START TIMER */
void timer_start(TIM_TypeDef *TIMx)
{
    TIMx->CR1 |= 1;
}

/* STOP TIMER */
void timer_stop(TIM_TypeDef *TIMx)
{
    TIMx->CR1 &= ~1;
}

/* ENABLE PERIODIC INTERRUPT */
void timer_enable_interrupt(TIM_TypeDef *TIMx)
{
    TIMx->DIER |= 1;

    if(TIMx == TIM2)
        NVIC_EnableIRQ(TIM2_IRQn);
    else if(TIMx == TIM3)
        NVIC_EnableIRQ(TIM3_IRQn);
}


/* PWM CONFIGURATION (Channel 1 example) */
void timer_pwm_init(TIM_TypeDef *TIMx, uint16_t prescaler, uint16_t arr, uint16_t duty)
{
    /* Enable clocks */
    RCC->APB1ENR |= (1<<1);   // TIM3
    RCC->APB2ENR |= (1<<2);   // GPIOA

    /* PA6 → Alternate Function Push Pull */
    GPIOA->CRL &= ~(0xF << 24);
    GPIOA->CRL |=  (0xB << 24);

    TIMx->PSC = prescaler;
    TIMx->ARR = arr;

    TIMx->CCR1 = duty;

    /* PWM Mode 1 */
    TIMx->CCMR1 |= (6 << 4);

    /* Enable channel */
    TIMx->CCER |= 1;

    /* Start timer */
    TIMx->CR1 |= 1;
}
