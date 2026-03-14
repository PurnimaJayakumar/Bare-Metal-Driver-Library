#ifndef GPIO_H
#define GPIO_H

#include "stm32l432xx.h"

/* Function declarations */

void GPIO_Init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);
uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);
void GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin);

#endif
