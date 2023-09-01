/* 
 * File:   dac_control.h
 * Author: ymaksime
 *
 * Created on August 31, 2023, 1:55 PM
 */

#ifndef DAC_CONTROL_H
#define	DAC_CONTROL_H

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
  Section: DAC_CONTROL APIs
*/
    
/**
  @Summary
    Initializes DAC related variables

  @Description
    This function initializes all required variables for the internal DAC.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
*/
void dac_control_init(void);

void dac_set(uint8_t dacVal);
uint8_t dac_get(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DAC_CONTROL_H */

