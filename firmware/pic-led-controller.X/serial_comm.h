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
#include "mcc_generated_files/mcc.h"
#include "version.h"
#include "adc_control.h"
#include "leds.h"
#include "light_control.h"
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

/**
  @Summary
    Set ADC active channel to 7

  @Description
    This function switches ADC active channel to channel 7, which is measuring
    the input voltage to the module, Vmeas signal on the schematic, RC3

  @Preconditions
    ADC_Initialize() and adc_control_init() function() should have been called

  @Param
    None

  @Returns
    None
*/
void func_adc_7(void);

/**
  @Summary
    Set ADC active channel to 5

  @Description
    This function switches ADC active channel to channel 5, which is measuring
    the output of the photo-resistor, SENSE-OUT signal on the schematic, RC1

  @Preconditions
    ADC_Initialize() and adc_control_init() function() should have been called

  @Param
    None

  @Returns
    None
*/
void func_adc_5(void);

/**
  @Summary
    Displays (RS232) the return value of read_milivolts() function

  @Description
    Use this function to output the return value of read_milivolts() fucntion
    over the RS232 channel.  Use func_adc_7() or func_adc_5() function to select
    desired ADC channel

  @Preconditions
    ADC_Initialize() and adc_control_init() functions should have been called

  @Param
    None

  @Returns
    None
*/
void func_adc_read(void);

/**
  @Summary
    Displays (RS232) current version of the Firmware code

  @Description
    Use this function to output the current Firmware version over the RS232

  @Preconditions
    EUSART_Initialize() function should have been called for the ISR to execute 
    correctly.

  @Param
    None

  @Returns
    None
*/
void func_version(void);

/**
  @Summary
    Controls whether to ECHO back the characters received over RS232

  @Description
    By default we want to disable echoing over RS232 to simplify the 
    communication between the module and Python scripts.  But at the same time 
    it is much more convenient when echo is enabled for a user.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void func_echo(void);

/**
  @Summary
    Controls the state of the LED ligth strip

  @Description
    Turns ON or OFF the LED light strip.  This function uses ramp-up and
    ramp-down functions to turn ON or OFF the external LED strip light

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void func_light_set(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	/* SERIAL_COMM_H */