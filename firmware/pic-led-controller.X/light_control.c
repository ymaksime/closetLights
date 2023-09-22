#include "light_control.h"

static uint16_t desired_pwm_value;
static uint16_t current_pwm_value;
static bool samples_ready;
static bool run_state_machine;
static bool validate_input_voltage;
static bool input_voltage_ok;

static void init_photoresistor_values(void);
static void update_photoresistor_values(void);

PhotoresistorReadings photoresistor;

void light_control_init(void) {
    // We are not ready to run full state-machine until we see eigth ADC sample
    samples_ready = false;
    // Do not run the state machine just yet, need to initialize everything
    run_state_machine = false;
    // Validate the input voltage as the first thing
    validate_input_voltage = true;
    input_voltage_ok = false;
    // Select "sensor" as our initial ADC channel
    adc_set_channel(sensor);
    // Initialize photoresistor related variables
    init_photoresistor_values();
    
    // Make sure we start with all lights OFF
    lights_off_immediately();
    
    // Set the custom ISR handler for Timer 6
    TMR6_SetInterruptHandler(pwm_control_isr_handler);
    // Set the custom ISR handler for Timer 1
    TMR1_SetInterruptHandler(statemachine_isr_handler);
    // Start the timer
    TMR1_StartTimer();
}

static void init_photoresistor_values(void) {
    for (int i = 0; i < SENSOR_SAMPLE_SIZE; i++) {
        photoresistor.readings_buffer[i] = 0;
    }
    photoresistor.buffer_full = false;
    photoresistor.current_state = SAME;
    photoresistor.index = 0;
    photoresistor.last_adc_reading = 0;
    photoresistor.running_average = 0;
    photoresistor.running_max = 0;
    photoresistor.running_min = 0xFFFF;
}

static void update_photoresistor_values(void) {
    // Assuming the ADC channel is set to "sensor" channel
    uint16_t adc_value = adc_read();
    
    // Even though we try to make sure the index is within the boundaries,
    // it is safer to check again
    if (photoresistor.index < SENSOR_SAMPLE_SIZE) {
        photoresistor.readings_buffer[photoresistor.index] = adc_value;
    }
    
    // Update MIN and MAX values
    if (photoresistor.running_max < adc_value) {
        photoresistor.running_max = adc_value;
    }
    if (photoresistor.running_min > adc_value) {
        photoresistor.running_min = adc_value;
    }
    
    // Update running average
    uint16_t temp = 0;
    for (int i = 0; i < SENSOR_SAMPLE_SIZE; i++) {
        temp += photoresistor.readings_buffer[i];
    }
    // Since the size of the buffer is a power of 2, we can just shift
    // to the right and avoid the division altogether.  Yes, we are loosing
    // resolution, but this is good enough
    photoresistor.running_average = temp >> SENSOR_SAMPLE_SHIFT;
    
    // Update the ambient state only after we have the full buffer of data
    if (photoresistor.buffer_full) {
        // We care only about a "dramatic" shift in ambient light intensity
        // This would indicate an open or closed door
        if (photoresistor.running_max - photoresistor.running_min > SENSOR_READINGS_DELTA) {
            // We know that this change was detected by the current reading
            // Find out which direction
            if (photoresistor.running_max == adc_value) {
                photoresistor.current_state = DARKER;
            }
            else {
                photoresistor.current_state = LIGHTER;
            }
        }
        else {
            photoresistor.current_state = SAME;
        }
    }
    
    // Update the last_adc_reading variable   
    photoresistor.last_adc_reading = adc_value;
    // Update the index
    // It should be the very last step
    if (++photoresistor.index >= SENSOR_SAMPLE_SIZE) {
        photoresistor.index = 0;
        // The "buffer_full" is need only at the beginning while we are filling
        // up the buffer
        photoresistor.buffer_full = true;
    }
}

void light_set_intensity(uint16_t new_pwm_value) {
    if (MAX_PWM_VALUE >= new_pwm_value) {
        desired_pwm_value = new_pwm_value;
    }    
}

void light_control_statemachine(void) {
    // Check if we need to validate input voltage
    if (validate_input_voltage) {
        // Make sure to reset the flag
        validate_input_voltage = false;
        // Get the value
        input_voltage_ok = is_input_voltage_ok();
    }
    // This state-machine is ran every time Timer 1 is elapses (100ms), unless
    // we need to check the input voltage
    else if (run_state_machine) {
        // Make sure to reset the flag
        run_state_machine = false;
        // Proceed if the input voltage is OK
        if (input_voltage_ok) {
            // First update the values for photoresistor
            update_photoresistor_values();
        }
    }
    // If input voltage is above the specs, turn off the LED
    if (!input_voltage_ok) {
        lights_off_immediately();
    }
}

bool is_input_voltage_ok(void) {
    bool result = false;
    // First, switch to the vMeas ADC channel
    adc_set_channel(vMeas);
    // After you switch ADC channel, it takes some time to fill up the ADC
    // buffer.  In our system we can assume 1ms per 1 ADC sample
    __delay_ms(ADC_SAMPLE_SIZE);
    // Now get the filtered reading of the input voltage
    uint16_t adc_value = adc_read();
    // Switch back to the "sensor" channel (default)
    adc_set_channel(sensor);

    if (MAX_VOLTAGE_READING < adc_value) {
        result = false;
    }
    else {
        result = true;
    }
        
    return result;
}

void lights_off_immediately(void) {
    // Probably not the most elegant way to do that, but it does its job
    desired_pwm_value = 0;
    current_pwm_value = 0;
    PWM3_LoadDutyValue(0);
}

void pwm_control_isr_handler(void) {
    if (current_pwm_value < desired_pwm_value) {
        PWM3_LoadDutyValue(++current_pwm_value);
    }
    else if (current_pwm_value > desired_pwm_value) {
        PWM3_LoadDutyValue(--current_pwm_value);
    }
}

void statemachine_isr_handler(void) {
    // Run the state-machine every 100ms
    run_state_machine = true;
    
    // Check the input voltage every 1000ms
    static uint8_t check_voltage_timer = 0;
    if (check_voltage_timer++ >= 10) {
        check_voltage_timer = 0;
        validate_input_voltage = true;
    }
}