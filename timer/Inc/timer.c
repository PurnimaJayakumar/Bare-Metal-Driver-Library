#include "ti_mer.h"

/* Callback pointer */
static void (*Timer_Callback)(void) = 0;

/* Enable Timer Clock */
static void Timer_EnableClock(TIM_TypeDef *TIMx)
{
    if (TIMx == TIM2)
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if (TIMx == TIM3)
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

/* INIT */
void Timer_Init(TIM_TypeDef *TIMx, Timer_Config_t *config)
{
    Timer_EnableClock(TIMx);

    TIMx->PSC = config->prescaler;
    TIMx->ARR = config->arr;
    TIMx->CNT = 0;

    /* Apply immediately */
    TIMx->EGR |= TIM_EGR_UG;
}

/* START */
void Timer_Start(TIM_TypeDef *TIMx)
{
    TIMx->CR1 |= TIM_CR1_CEN;
}

/* STOP */
void Timer_Stop(TIM_TypeDef *TIMx)
{
    TIMx->CR1 &= ~TIM_CR1_CEN;
}

/* RESET */
void Timer_Reset(TIM_TypeDef *TIMx)
{
    TIMx->CNT = 0;
}

/* INTERRUPT ENABLE */
void Timer_EnableInterrupt(TIM_TypeDef *TIMx)
{
    TIMx->DIER |= TIM_DIER_UIE;

    if (TIMx == TIM2)
        NVIC_EnableIRQ(TIM2_IRQn);
    else if (TIMx == TIM3)
        NVIC_EnableIRQ(TIM3_IRQn);
}

/* SET CALLBACK */
void Timer_SetCallback(void (*callback)(void))
{
    Timer_Callback = callback;
}

/* ISR */
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;

        if (Timer_Callback)
            Timer_Callback();
    }
}

void TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;

        if (Timer_Callback)
            Timer_Callback();
    }
}

/* PWM INIT */
void Timer_PWM_Init(TIM_TypeDef *TIMx, Timer_Config_t *config)
{
    Timer_EnableClock(TIMx);

    TIMx->PSC = config->prescaler;
    TIMx->ARR = config->arr;

    /* PWM Mode 1 */
    TIMx->CCMR1 |= (6 << 4);

    /* Preload enable */
    TIMx->CCMR1 |= TIM_CCMR1_OC1PE;
    TIMx->CR1   |= TIM_CR1_ARPE;

    /* Enable channel 1 */
    TIMx->CCER |= TIM_CCER_CC1E;

    TIMx->EGR |= TIM_EGR_UG;
}

/* SET DUTY (0–100%) */
void Timer_PWM_SetDuty(TIM_TypeDef *TIMx, uint32_t duty)
{
    TIMx->CCR1 = (TIMx->ARR * duty) / 100;
}
