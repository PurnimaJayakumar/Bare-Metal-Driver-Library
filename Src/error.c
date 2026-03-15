#include "inc/error.h"
#include <stddef.h>

// Setting default to success (no error)
static ErrorCode current_error = SUCCESS;

// Allows to set ErrorCode
void error_set(ErrorCode code){
    current_error = code;
}

// Allows to see the error
ErrorCode error_get(void){
    return current_error;
}

// Set ErrorCode to SUCCESS
void error_clear(void){
    current_error = SUCCESS;
}

// To return error status as strings
const char* error_to_string(ErrorCode code){
    switch(code){
        // General Errors
        case SUCCESS: return "Success";
        case ERROR_GENERAL: return "General Error";
        case ERROR_TIMEOUT: return "Timeout Error";
        case ERROR_INVALID_ARG: return "Invalid Argument";
        case ERROR_BUSY: return "Resource Busy";

        // GPIO Errors
        case ERROR_GPIO_INVALID_PIN: return "GPIO: Invalid Pin";
        case ERROR_GPIO_INVALID_PORT: return "GPIO: Invalid Port";
        case ERROR_GPIO_CONFIG_FAILED: return "GPIO: Configuration Failed";
        case ERROR_GPIO_INVALID_MODE: return "GPIO: Invalid Mode";

        // UART Errors
        case ERROR_UART_BUFFER_FULL: return "UART: Buffer Full";
        case ERROR_UART_FRAMING: return "UART: Framing Error";
        case ERROR_UART_NOISE: return "UART: Noise Error";
        case ERROR_UART_OVERRUN: return "UART: Overrun Error";
        case ERROR_UART_PARITY: return "UART: Parity Error";
        case ERROR_UART_DMA_TRANSFER: return "UART: DMA Transfer Error";
        case ERROR_UART_UNINITIALIZED: return "UART: Uninitialized";

        // SPI Errors
        case ERROR_SPI_MODE_FAULT: return "SPI: Mode Fault";
        case ERROR_SPI_CRC: return "SPI: CRC Error";
        case ERROR_SPI_OVERRUN: return "SPI: Overrun Error";
        case ERROR_SPI_FLAG: return "SPI: Flag Error";
        case ERROR_SPI_DMA_TRANSFER: return "SPI: DMA Transfer Error";
        case ERROR_SPI_UNINITIALIZED: return "SPI: Uninitialized";

        // Timer Errors
        case ERROR_TIMER_INVALID_CHANNEL: return "Timer: Invalid Channel";
        case ERROR_TIMER_INVALID_PRESCALER: return "Timer: Invalid Prescaler";
        case ERROR_TIMER_INVALID_PERIOD: return "Timer: Invalid Period";
        case ERROR_TIMER_NOT_ENABLED: return "Timer: Not Enabled";
        case ERROR_TIMER_UNINITIALIZED: return "Timer: Uninitialized";

        // Interrupt Errors
        case ERROR_INTERRUPT_INVALID_VECTOR: return "Interrupt: Invalid Vector";
        case ERROR_INTERRUPT_INVALID_PRIORITY: return "Interrupt: Invalid Priority";
        case ERROR_INTERRUPT_HANDLER_NOT_INSTALLED: return "Interrupt: Handler Not Installed";

        default:
            return "Unknown Error";
    }
}