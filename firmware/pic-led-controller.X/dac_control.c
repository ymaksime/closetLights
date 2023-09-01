/**
  Section: Included Files
*/
#include "dac_control.h"

/**
  Section: Global Variables
*/

/**
  Section: private function and variables
*/

void dac_control_init(void) {
    
    // Make sure that the DAC is set at 0 at the power-up
    DAC_SetOutput(0);
}

void dac_set(uint8_t dacVal) {
    DAC_SetOutput(dacVal);
}

uint8_t dac_get(void) {
    return DAC_GetOutput();
}