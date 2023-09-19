/* 
 * File:   light.h
 * Author: ymaksime
 *
 * Created on September 13, 2023, 4:27 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"
#include "dac_control.h"
#include "leds.h"

#ifdef	__cplusplus
extern "C" {
#endif

/**
  @Summary
    Converts milli-amps into corresponding DAC value

  @Description
    It was emperically determined that the relationship between DAC and 
    milli-amps can be characterized by the following linear equation:
        mA = 7.814 * DAC - 1.065
    After solving for DAC, we have the following:
        DAC = (mA + 1.065) / 7.814
    To make it more useful for setting DAC, we need to round up the answer to 
    the nearest integer
        DAC = round_up( (mA + 1.065) / 7.814) | mA: 0 - 1999
    This equation can be further simplified to use only subtract and bit-shift
    operations:
        AC = (mA + 2) >> 3 | mA: 0 - 1999

  @Preconditions
    None

  @Param
    milliAmp: value in milli-amps to convert into DAC (16-bit value).  Expected
    range is 0 - 2000.  If the requested value is out of the range, the function
    returns 0.

  @Returns
    DAC value corresponding to the requested milliAmp (8-bit value)
*/
uint8_t milli_amps_to_dac(uint16_t milliAmp);

void light_control_init(void);
void light_control_isr_handler(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_H */

