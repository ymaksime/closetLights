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

void light_control_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_H */

