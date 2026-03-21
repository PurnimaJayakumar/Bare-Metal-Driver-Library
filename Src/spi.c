/**
 * @file spi.c
 * @brief SPI1 Driver for STM32L432KC (Master Mode)
 * * ============================================================================
 * USAGE GUIDELINES
 * ============================================================================
 * 1. INITIALIZATION: 
 * Call SPI1_Master_Init() once at the start of your program to configure 
 * clocks, GPIOs (PA4-PA7), and the SPI1 peripheral.
 * * 2. COMMUNICATION SEQUENCE:
 * SPI communication must follow a "Frame" structure using the Chip Select (CS) pin:
 * * a) Start Frame: Call SPI1_CS_Enable() to select the slave device.
 * b) Data Exchange: Call SPI1_Transfer(data) for every byte you wish to swap.
 * Note: SPI is full-duplex; every transfer sends a byte and returns one.
 * c) End Frame: Call SPI1_CS_Disable() to release the slave device.
 * * 3. IMPORTANT:
 * - The driver is blocking; it will wait until the hardware buffer is ready.
 * - To ensure data integrity, do not call SPI1_CS_Disable() until the 
 * SPI1_Transfer() has returned the final byte.
 * * EXAMPLE:
 * SPI1_CS_Enable();
 * SPI1_Transfer(REG_ADDRESS | READ_BIT);
 * uint8_t received_val = SPI1_Transfer(0x00); // Send dummy to read response
 * SPI1_CS_Disable();
 * ============================================================================
 */

#include<stm32l432xx.h>
void SPI1_Master_Init(void){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // provides the clock cycle for alternative function of GPIO pin
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //Gives clock cycle to the SPI1 peripheral

    GPIOA->MODER &= ~(3UL << (5*2)); // Alternate Pin 5 for first clearing and then setting it to alternate function for SPI1_SCLK (clock)
    GPIOA->MODER |= (2UL << (5*2));
    GPIOA->MODER &= ~(3UL << (6*2)); //pin 6 for (first cleared and then set to for alternate function) for SPI1_MISO
    GPIOA->MODER |= (2UL << (6*2));
    GPIOA->MODER &= ~(3UL << (7*2)); //pin 7 for (first cleared and then set to for alternate function) for SPI1_MOSI
    GPIOA->MODER |= (2UL << (7*2));

    GPIOA->AFR[0] &= ~(15UL << (5*4)); //Enabling the AF(lower) for connecting the CLK to AF5
    GPIOA->AFR[0] |= (5UL << (5*4));
    GPIOA->AFR[0] &= ~(15UL << (6*4)); //Enabling the AF(lower) for connecting the MISO wires to the AF5
    GPIOA->AFR[0] |= (5UL << (6*4));
    GPIOA->AFR[0] &= ~(15UL << (7*4)); //Enabling the AF(lower) for connecting the MOSI wires to the AF5
    GPIOA->AFR[0] |= (5UL << (7*4));

    SPI1->CR1 &= ~(1UL << 2);  //Enabling the SPI1_CR1 register as the Master(after clearing and then setting)
    SPI1->CR1 |= (1UL << 2);  

    SPI1->CR1 |= (3UL << 3); // setting the Baud Rate as fPCLK/16 for the communication with peripheral 

    SPI1->CR1 |= (1UL << 9); // Enabling the SSM(Software Slave Management) 
    SPI1->CR1 |= (1UL << 8); // Enabling the SSI(Internal Slave Select)
    SPI1->CR1 &= ~(1UL << 1); // Setting CPOL to 0 (Clock idles LOW) CPOL->Clock Polarity 
    SPI1->CR1 &= ~(1UL << 0); // Setting CPHA to 0 (Data captured on first edge) CPHA-> Clockk Phase

    SPI1->CR2 &= ~(15UL << 8); //clearing the bits for setting the correct data size of comuunication 
    SPI1->CR2 |= (7UL << 8); // Setting the data size as 8 bit for communication at a time 
    SPI1->CR2 |= (1UL << 12); // Setting the (FRXTH) (FIFO reception threshold)

    GPIOA->MODER &= ~(3UL << (4*2));  // Enabling the CS line to set the GPIO 4 pin to behave as output mode
    GPIOA->MODER |= (1UL << (4*2));  

    GPIOA->BSRR |= (1UL << 4); //Setting the GPIO 4 pin as 'HIGH' by default 

    SPI1->CR1 |= (1UL << 6); // Switching ON the SPI module
}

uint8_t SPI1_Transfer(uint8_t data){

    while(!(SPI1->SR & SPI_SR_TXE)); // check for seeing if the TXE(Transmit buffer empty) indicating if DR(Data Register) is empty (HIGH) or not (LOW) for incoming data

    *((volatile uint8_t *)& SPI1->DR) = data; 

    while(!(SPI1->SR & SPI_SR_RXNE)); // check for verifying if RXNE(Reciever Buffer Not Empty) indicating if DR has incoming data lined up (HIGH) or not (LOW)

    uint8_t result = *((volatile uint8_t *)&SPI1->DR);

    while(SPI1->SR & SPI_SR_BSY); return result; // returning the recieved data back to the DR if the the SPI is not working using the BSY Flag
}

void SPI1_CS_Enable(void){  
        GPIOA->BSRR |= (1UL << 20);   // resetting the 4th bit of BSRR to enable communicaton process
} 

void SPI1_CS_Disable(void){
        GPIOA->BSRR |= (1UL << 4);  // setting the 4th bit of BSRR to disable the communication
} 