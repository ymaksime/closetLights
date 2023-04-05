/* 
 * File:   serialComm.h
 * Author: ymaksime
 *
 * Created on January 10, 2023, 3:26 PM
 */

#ifndef SERIAL_COMM_H
#define	SERIAL_COMM_H

/**
  Section: Included Files
*/
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/eusart.h"
#include "mcc_generated_files/adc.h"
#include "version.h"
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Macro Declarations
*/
#define EUSART_RX_BUFFER_SIZE 32
#define CMD_BUFFER_SIZE 32
#define CMD_SIZE 4

#define BACKSPACE 8
#define LF 10
#define CR 13
#define SPACE 32
#define INIT_CHAR SPACE

/**
 Section: Global variables
 */
//extern volatile uint8_t eusartRxCount;
//extern volatile uint8_t eusartRxBuffer[EUSART_RX_BUFFER_SIZE];

/**
  Section: SERIAL_COMM APIs
*/

/**
  @Summary
    Initializes serial communication

  @Description
    This function initializes all required variables for serial communication.
    Additionally, it EUSART_SetTxInterruptHandler to point to the custom Rx
    ISR handler.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void serial_comm_init(void);

/**
  @Summary
    Custom Rx ISR handler

  @Description
    This function will be called from within eusart.c file to service receive
    interrupts.  Inside it uses a buffer of size EUSART_RX_BUFFER_SIZE to store
    the received characters (char8_t).  It checks for overflows and other 
    possible errors.

  @Preconditions
    EUSART_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void serial_comm_rx_ISR(void);

/**
  @Summary
    Communication statemachine

  @Description
    This statemachine handles the serial communication process between the uC
    and the outside world.

  @Preconditions
    EUSART_Initialize() function should have been called
    for the ISR to execute correctly.

  @Param
    None

  @Returns
    None
*/
void serial_comm_check(void);

void func_led_r(void);
void func_led_g(void);
void func_adc_7(void);
void func_adc_5(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	/* SERIAL_COMM_H */