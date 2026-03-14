#ifndef GPIO_H
#define GPIO_H

#include "stm32l432xx.h"
#include <stdint.h>

/* GPIO Modes */
#define GPIO_MODE_INPUT      0
#define GPIO_MODE_OUTPUT     1
#define GPIO_MODE_ALT        2
#define GPIO_MODE_ANALOG     3

/* Output Types */
#define GPIO_OTYPE_PP        0
#define GPIO_OTYPE_OD        1

/* Pull Configuration */
#define GPIO_NOPULL          0
#define GPIO_PULLUP          1
#define GPIO_PULLDOWN        2

/* Speed */
#define GPIO_SPEED_LOW       0
#define GPIO_SPEED_MEDIUM    1
#define GPIO_SPEED_HIGH      2
#define GPIO_SPEED_VERYHIGH  3

/* Function Prototypes */

void GPIO_Init(GPIO_TypeDef *port,
               uint8_t pin,
               uint8_t mode,
               uint8_t otype,
               uint8_t pull,
               uint8_t speed);

void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);

uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);

void GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin);

#endif
