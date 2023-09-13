/* 
 * File:   adc_control.h
 * Author: ymaksime
 *
 * Created on April 5, 2023, 1:44 PM
 */

#ifndef ADC_CONTROL_H
#define	ADC_CONTROL_H

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"
#include "leds.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
 /**
  Section: Macro Declarations
*/
#define ADC_SAMPLE_SHIFT (3)
#define ADC_SAMPLE_SIZE (1 << ADC_SAMPLE_SHIFT)
    
    
/**
  Section: ADC_CONTROL APIs
*/

/**
  @Summary
    Initializes adc related variables

  @Description
    This function initializes all required variables for the internal ADC.
    Additionally, it uses ADC_SetInterruptHandler to point to the custom ADC
    ISR handler.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void adc_control_init(void);

/**
  @Summary
    Returns averaged value of the circular buffer

  @Description
    After disabling TIM2 interrupt, it finds the rounded down averaged value
    of the ADC readings stored in circular buffer of size ADC_SAMPLE_SIZE
   
    To convert to millivolts, do the following:
    millivolts = adc_val * 2048 / 1024
    where 
    * 2048 is our internal voltage reference in millivolts
    * 1024 = 10-bit value from ADC
    Example: millivolts = 282 * 2048 / 1024 = 564 mV

  @Preconditions
    None

  @Param
    None

  @Returns
    Averaged and rounded down content of the circular buffer
*/
uint16_t adc_read(void);

/**
  @Summary
    Handles ADC interrupts

  @Description
    Continuously updates internal circular buffer with new ADC readings of the 
    active channel.  This ISR is triggered by Timer_2 which has a 1 millisecond
    period.

  @Preconditions
    None

  @Param
    None

  @Returns
*/
void adc_control_isr_handler(void);

/**
  @Summary
    Sets active ADC channel

  @Description
    Call this function to set active ADC channel.  The parameter is ignored if 
    it is an invalid option or the active channel is the requested one

  @Preconditions
    None

  @Param
    None

  @Returns
*/
void adc_set_channel(adc_channel_t chan);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_CONTROL_H */

