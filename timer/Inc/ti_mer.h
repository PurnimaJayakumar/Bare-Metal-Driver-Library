#ifndef TIMER_H
#define TIMER_H

#include "stm32f1xx.h"

/* Timer Configuration Structure */
typedef struct
{
    uint16_t prescaler;
    uint16_t arr;
} Timer_Config_t;

/* Basic Timer Configuration */
void Timer_Init(TIM_TypeDef *TIMx, Timer_Config_t *config);

/* Start / Stop / Reset */
void Timer_Start(TIM_TypeDef *TIMx);
void Timer_Stop(TIM_TypeDef *TIMx);
void Timer_Reset(TIM_TypeDef *TIMx);

/* Interrupt Handling */
void Timer_EnableInterrupt(TIM_TypeDef *TIMx);
void Timer_SetCallback(void (*callback)(void));

/* PWM Configuration */
void Timer_PWM_Init(TIM_TypeDef *TIMx, Timer_Config_t *config);
void Timer_PWM_SetDuty(TIM_TypeDef *TIMx, uint16_t duty);

#endif
