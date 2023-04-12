/**
  Section: Included Files
*/
#include "serial_comm.h"

/**
  Section: Global Variables
*/
// Used for converting binary to ASCII
const unsigned char convertnibble[] = "0123456789ABCDEF";
// Used to store final command from the user
uint8_t cmdBuffer[CMD_BUFFER_SIZE];

/**
  Section: private function for EUSART APIs
*/
static void send8BytesAsAsciiHex(uint8_t data);
static void send16BytesAsAsciiHex(uint16_t data);
static void sendString(char* str);
static void handleBackspace(void);
static void handleCR(void);
static void updateRxBuffer(uint8_t rxData);
static void handleCmdCall(char *buf);
void serial_comm_OverrunErrorHandler(void);

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

static void sendString(char* str) {
    while (*str) {
        EUSART_Write(*str++);
    }
    handleCR();
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
    
    // List of all the mnemonics of the available functions
    static const char read_str[] = 
    "LEDR LEDG ADC5 ADC7 ADCR VERG";
    
    // List of function pointers
    // Every entry corresponds to an entry in the read_str[] array
    static void (* const readfns[sizeof(read_str)/(CMD_SIZE + 1)])(void) =
    {
        func_led_r, func_led_g, func_adc_5, func_adc_7, func_adc_read,
        func_version
    };
    
    // Find the index of the first match
    cmdptr = strstr(read_str, buf);
    if (cmdptr != NULL) {
        // Compute the offset based on mnemonic size
        offset = (cmdptr - read_str) / (CMD_SIZE + 1);
        // Find the function pointer
        readfns[offset]();
    }
}

void func_led_r(void) {
    ledRed_Toggle();
}

void func_led_g(void) {
    ledGrn_Toggle();
    send8BytesAsAsciiHex(TMR2_ReadTimer());
    handleCR();
}

void func_adc_5(void) {
    // Set the appropriate ADC channel: sensor
    adc_set_channel(sensor);
}

void func_adc_7(void) {
    // Set the appropriated ADC channel: vMeas, the input voltage
    adc_set_channel(vMeas);
}

void func_adc_read(void) {
    // Get the averaged data for the active ADC channel
    send16BytesAsAsciiHex(read_milivolts());
    handleCR();
}

void func_version(void) {
    sendString(VERSION);
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