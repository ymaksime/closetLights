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
#include "adc_control.h"
#include "leds.h"
#include "serial_comm.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
/**
  Section: Macro Declarations
*/
#define SENSOR_SAMPLE_SHIFT (3)
#define SENSOR_SAMPLE_SIZE (1 << SENSOR_SAMPLE_SHIFT)
    // The PWM block is set up to have maximum value of 999 as 99.9%
#define MAX_PWM_VALUE 999
    // The vMeas channel is connected to a voltage divider (200K + 10K) between
    // Vin and GND.  The Vout = Vin(10K/(200K + 10K)). If we say that the
    // maxim allowed Vin should be no greater than 12.8V, then it corresponds
    // to 0.60952V or 610mV.  The corresponding ADC value would be equal to half
    // of this, i.e. 305.  See additional info for adc_read() function.
    // To account for the tolorances in the resistive network, we should lower
    // the value
#define MAX_VOLTAGE_READING 290
    // Maximum delta between MAX and MIN readings of the photoresistor sensor
    // If exceeded, we need have a "significant" ambient light intesnsity change
    // and need to update the system
#define SENSOR_READINGS_DELTA 200
    // States of ambient light intensity change
typedef enum { LIGHTER, DARKER, SAME } AmbientState;
    
typedef struct {
    uint16_t last_adc_reading;
    uint16_t running_max;
    uint16_t running_min;
    uint16_t running_average;
    uint16_t readings_buffer[SENSOR_SAMPLE_SIZE];
    uint8_t  index;
    bool     buffer_full;
    AmbientState current_state;
} PhotoresistorReadings;

void light_control_init(void);
void light_set_intensity(uint16_t new_pwm_value);
void light_control_statemachine(void);
void pwm_control_isr_handler(void);
void statemachine_isr_handler(void);
void external_control_isr_handler(void);
bool is_input_voltage_ok(void);
bool is_input_voltage_ok_2(void);
void lights_off_immediately(void);
#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_H */

