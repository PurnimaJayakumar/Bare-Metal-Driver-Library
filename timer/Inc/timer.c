#include "ti_mer.h"

/* BASIC TIMER CONFIGURATION */
void timer_basic_init(TIM_TypeDef *TIMx, uint32_t prescaler, uint32_t arr)
{
    /* Enable clock for timer */
    if(TIMx == TIM2)
        RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    else if(TIMx == TIM3)
        RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

    TIMx->PSC = prescaler;   // Prescaler
    TIMx->ARR = arr;         // Auto reload register
    TIMx->CNT = 0;
}

/* START TIMER */
void timer_start(TIM_TypeDef *TIMx)
{
    TIMx->CR1 |= TIM_CR1_CEN;
}

/* STOP TIMER */
void timer_stop(TIM_TypeDef *TIMx)
{
    TIMx->CR1 &= ~TIM_CR1_CEN;
}

/* ENABLE PERIODIC INTERRUPT */
void timer_enable_interrupt(TIM_TypeDef *TIMx)
{
    TIMx->DIER |= TIM_DIER_UIE;

    if(TIMx == TIM2)
        NVIC_EnableIRQ(TIM2_IRQn);
    else if(TIMx == TIM3)
        NVIC_EnableIRQ(TIM3_IRQn);
}

/* PWM USING TIM3 CHANNEL 1 */
void timer_pwm_init(uint32_t prescaler, uint32_t arr, uint32_t duty)
{
    /* Enable clocks */
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
    RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOAEN;

    /* PA6 alternate function mode */
    GPIOA->MODER &= ~(3 << (6*2));
    GPIOA->MODER |=  (2 << (6*2));

    /* AF2 for TIM3 */
    GPIOA->AFR[0] &= ~(0xF << (6*4));
    GPIOA->AFR[0] |=  (2 << (6*4));

    /* Timer configuration */
    TIM3->PSC = prescaler;
    TIM3->ARR = arr;

    /* Duty cycle */
    TIM3->CCR1 = duty;

    /* PWM mode 1 */
    TIM3->CCMR1 |= (6 << 4);

    /* Enable channel */
    TIM3->CCER |= TIM_CCER_CC1E;

    /* Start timer */
    TIM3->CR1 |= TIM_CR1_CEN;
}
