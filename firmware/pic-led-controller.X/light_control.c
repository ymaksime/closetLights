#include "light_control.h"

static uint16_t desired_pwm_value;

void light_control_init(void) {
    // Set the custom ADC ISR handler
    TMR6_SetInterruptHandler(light_control_isr_handler);
}

void light_set_intensity(uint16_t new_pwm_value) {
    if (MAX_PWM_VALUE >= new_pwm_value) {
        desired_pwm_value = new_pwm_value;
    }    
}

void light_control_isr_handler(void) {
    static uint16_t current_pwm_value = 0;
    if (current_pwm_value < desired_pwm_value) {
        PWM3_LoadDutyValue(++current_pwm_value);
    }
    else if (current_pwm_value > desired_pwm_value) {
        PWM3_LoadDutyValue(--current_pwm_value);
    }
}