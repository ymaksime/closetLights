/**
  Section: Included Files
*/
#include "serial_comm.h"

/**
  Section: Global Variables
*/
// Used for converting binary to ASCII
const unsigned char convertnibble[] = "0123456789ABCDEF";

/**
  Section: EUSART APIs
*/
static void send8BytesAsAsciiHex(uint8_t data);
static void send16BytesAsAsciiHex(uint16_t data);
static void handleBackspace(void);
static void handleCR(void);
static void updateRxBuffer(uint8_t rxData);
static void handleCmdCall(char *buf);
void serial_comm_OverrunErrorHandler(void);

uint8_t cmdBuffer[CMD_BUFFER_SIZE];

void serial_comm_init(void) {
    // Set a custom ISR handler
    //EUSART_SetTxInterruptHandler(serial_comm_rx_ISR);
    // Set a custom Overrun Error Handler (same as default one)
    //EUSART_SetOverrunErrorHandler(serial_comm_OverrunErrorHandler);
    
    // Initialize global and local variables
    for (int i = 0; i < CMD_BUFFER_SIZE; i++) {
        cmdBuffer[i] = INIT_CHAR;
    }
}

void serial_comm_check(void) {
    
    uint8_t rxChar;
    // Check if we received anything
    if (EUSART_is_rx_ready()) {
        // Echo back the received character
        rxChar = EUSART_Read();
        
        if (BACKSPACE == rxChar) {
            handleBackspace();
        } else if (CR == rxChar) {
            handleCR();
        }else {
            EUSART_Write(rxChar);
        }
        
        // Store the character in RX buffer
        updateRxBuffer(rxChar);
    }
}

static void send8BytesAsAsciiHex(uint8_t data) {
    // Convert and send the first four bytes of the data
    unsigned char temp = convertnibble[(uint8_t)(data >> 4)];
    EUSART_Write(temp);
    // Now deal with the second half of the data
    temp = convertnibble[(uint8_t)(data & 0x0f)];
    EUSART_Write(temp);
}

static void send16BytesAsAsciiHex(uint16_t data) {
    // Send the first half
    send8BytesAsAsciiHex(data >> 8);
    // Now deal with the second half
    send8BytesAsAsciiHex(data & 0xff);
}

static void handleBackspace(void) {
    // First, send the backspace character back to return the cursor
    EUSART_Write(BACKSPACE);
    // Next, send the space character to clear the previous character
    EUSART_Write(SPACE);
    // Finally, return the cursor back one position
    EUSART_Write(BACKSPACE);
}

static void handleCR(void) {
    // First, return to index 0 of the current line
    EUSART_Write(CR);
    // Next, jump to the next line
    EUSART_Write(LF);
}

static void updateRxBuffer(uint8_t rxData) {
    // This is our pointer to the current location of in the RX buffer
    static int rxIndex = 0;
    // We will store the received four letter function mnemonic here
    static char rx_cmd[CMD_SIZE + 1];
    
    // We received a Carriage Return, which means we need to process the command
    if (CR == rxData) {
        
        // Copy the first four characters from the rx buffer to the command
        // call pointer assuming that it is a command call
        for (int i = 0; i < CMD_SIZE; i++ ) {
            rx_cmd[i] = cmdBuffer[i];
        }
        // Now let's deal with the command
        handleCmdCall(rx_cmd);
        
        // TODO: process the command
//        for (int j = 0; j < CMD_BUFFER_SIZE; j++) {
//            EUSART_Write(cmdBuffer[j]);
//        }
//        handleCR();

        // Re-initialize the RX buffer
        for (int i = 0; i < CMD_BUFFER_SIZE; i++) {
            cmdBuffer[i] = INIT_CHAR;
        }
        rxIndex = 0;
    } else {
        // Add next character only if we still have space in the buffer
        if (rxIndex < CMD_BUFFER_SIZE) {
            // Deal with the Backspace character
            if (BACKSPACE == rxData) {
                // Delete the last character only if we have something stored
                if (0 != rxIndex) {
                    rxIndex--;
                    cmdBuffer[rxIndex] = INIT_CHAR;
                }
            // This is just a regular character, store it
            } else {
                cmdBuffer[rxIndex] = rxData;
                rxIndex++;
            }     
        }
    }
}

static void handleCmdCall(char *buf) {
    char *cmdptr;
    int offset;
    
    static const char read_str[] = 
    "LEDR LEDG ADC5 ADC7";
    
    static void (* const readfns[sizeof(read_str)/(CMD_SIZE + 1)])(void) =
    {
        func_led_r, func_led_g, func_adc_5, func_adc_7
    };
    
    cmdptr = strstr(read_str, buf);
    if (cmdptr != NULL) {
        offset = (cmdptr - read_str) / (CMD_SIZE + 1);
        readfns[offset]();
    }
}

void func_led_r(void) {
    ledRed_Toggle();
}

void func_led_g(void) {
    ledGrn_Toggle();
}

void func_adc_5(void) {
    adc_result_t temp = ADC_GetConversion(sensor);
    send16BytesAsAsciiHex(temp);
    handleCR();
}

void func_adc_7(void) {
    adc_result_t temp = ADC_GetConversion(vMeas);
    send16BytesAsAsciiHex(temp);
    handleCR();
}


void serial_comm_rx_ISR(void) {
    if (RC1STAbits.OERR) {
        serial_comm_OverrunErrorHandler();
    }
}

void serial_comm_OverrunErrorHandler(void) {
    // EUSART error - restart
    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;
}