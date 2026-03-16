#ifndef TIMER_H
#define TIMER_H

#include "stm32f1xx.h"

/* Basic Timer Configuration */
void timer_basic_init(TIM_TypeDef *TIMx, uint16_t prescaler, uint16_t arr);

/* Start and Stop */
void timer_start(TIM_TypeDef *TIMx);
void timer_stop(TIM_TypeDef *TIMx);

/* Enable Periodic Interrupt */
void timer_enable_interrupt(TIM_TypeDef *TIMx);

/* PWM Configuration */
void timer_pwm_init(TIM_TypeDef *TIMx, uint16_t prescaler, uint16_t arr, uint16_t duty);

#endif
