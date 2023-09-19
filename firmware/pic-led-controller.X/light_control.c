#include "light_control.h"

void light_control_init(void) {
    // Set the custom ADC ISR handler
    TMR4_SetInterruptHandler(light_control_isr_handler);
}

uint8_t milli_amps_to_dac(uint16_t milliAmp) {
    uint8_t dac_val = 0;
        
    // Make sure you are within the range
    if (2000 > milliAmp) {
        dac_val = (milliAmp + 2) >> 3;
    }
    
    return dac_val;
}

void light_control_isr_handler(void) {
    // This is for debugging, LED heartbeat
    static uint16_t i;    
    if (++i >= 50) {
        toggle_green_led();
        i = 0;
    }
}