#ifndef SPI_H
#define SPI_H

#include<stm32l432xx.h>
/**
 * @brief Initializes SPI1 in Master Mode (8-bit, Mode 0, fPCLK/16)
 * Configures PA5 (SCK), PA6 (MISO), PA7 (MOSI) and PA4 (CS)
 */
void SPI1Master_Init(void);
/**
 * @brief Swaps one byte of data over the SPI1 bus
 * @param data The byte to send
 * @return The byte received from the slave
 */
uint8_t SPI1_Transfer(uint8_t data);
/**
 * @brief Pulls the Chip Select (PA4) LOW to start communication
 */
void SPI1_CS_Enable(void);
/**
 * @brief Pulls the Chip Select (PA4) HIGH to end communication
 */
void SPI1_CS_Disable(void);

#endif