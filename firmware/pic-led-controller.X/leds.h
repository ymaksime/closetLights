/* 
 * File:   leds.h
 * Author: ymaksime
 *
 * Created on September 13, 2023, 2:00 PM
 */

#ifndef LEDS_H
#define	LEDS_H

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"

#ifdef	__cplusplus
extern "C" {
#endif

/**
  Section: Macro Declarations
*/
    
/**
  Section: SERIAL_COMM APIs
*/
    void turn_off_red_led(void);
    void turn_on_red_led(void);
    void toggle_red_led(void);
    
    void turn_off_green_led(void);
    void turn_on_green_led(void);
    void toggle_green_led(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */

