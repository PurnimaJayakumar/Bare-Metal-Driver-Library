#include "gpio.h"

void GPIO_EnableClock(GPIO_TypeDef *port)
{
    if(port == GPIOA)
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
  else if(port == GPIOB)
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
  else if(port == GPIOC)
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
  else if(port == GPIOD)
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
  else if(port == GPIOE)
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
}

void GPIO_Init(GPIO_TypeDef *port,
               uint8_t pin,
               uint8_t mode,
               uint8_t otype,
               uint8_t pull,
               uint8_t speed)
{
 /* Configure pin mode */
    port->MODER &= ~(3 << (2 * pin));
    port->MODER |= (mode << (2 * pin));
 /* Configure output type */
    port->OTYPER &= ~(1 << pin);
    port->OTYPER |= (otype << pin);
  /* Configure speed */
    port->OSPEEDR &= ~(3 << (2 * pin));
    port->OSPEEDR |= (speed << (2 * pin));
 /* Configure pull-up/pull-down */
    port->PUPDR &= ~(3 << (2 * pin));
    port->PUPDR |= (pull << (2 * pin));
}

void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value)
{
    if(value)
        port->BSRR = (1 << pin);           // Set pin
    else
        port->BSRR = (1 << (pin + 16));    // Reset pin
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin)
{
    return (port->IDR >> pin) & 0x01;
}

void GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin)
{
    port->ODR ^= (1 << pin);
}
