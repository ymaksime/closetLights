/**
  Section: Included Files
*/
#include "adc_control.h"

/**
  Section: Global Variables
*/
// Internal circular buffer to store ADC readings
volatile adc_result_t adcBuffer[ADC_SAMPLE_SIZE];

/**
  Section: private function and variables
*/
// Currently active ADC channel
static adc_channel_t adcChan;
// Initialize ADC buffer
static void init_adc_buffer(void);

void adc_control_init(void) {
    // Initialize variables
    for (int i = 0; i < ADC_SAMPLE_SIZE; i++) {
        adcBuffer[i] = 0;
    }
    
    // Set the custom ADC ISR handler
    ADC_SetInterruptHandler(adc_control_isr_handler);
    
    // Set the active channel
    adcChan = vMeas;
    ADC_SelectChannel(adcChan);
}

void adc_set_channel(adc_channel_t chan) {
    // Don't do anything if the requested channel is what we already have
    if (adcChan != chan) {
        
        // Since we a changing the ADC channel, all of the stored value in the
        // ADC buffer are no longer valid and we need to clear them off
        init_adc_buffer();
        
        // Now change the channel
        adcChan = chan;
        ADC_SelectChannel(adcChan);
    }
}

uint16_t adc_read(void) {
    // Stop the timer to make sure we don't get interrupted
    TMR2_StopTimer();
    
    // Just in case the ADC conversion was started
    while (!ADC_IsConversionDone()) {
    }
    
    // Now get the sum of all values in the buffer
    uint16_t result = 0;
    for (int i = 0; i < ADC_SAMPLE_SIZE; i++) {
        result += adcBuffer[i];
    }
    
    // Since the size of the buffer is a power of 2, we can just shift
    // to the right and avoid the division altogether.  Yes, we are loosing
    // resolution, but this is good enough
    result = result >> ADC_SAMPLE_SHIFT;
    
    // Start the timer
    TMR2_StartTimer();
    
    return result;
}

static void init_adc_buffer(void) {
    // Stop the timer to make sure we don't get interrupted
    TMR2_StopTimer();
    
    // Just in case the ADC conversion was started
    while (!ADC_IsConversionDone()) {
    }
    
    // Initialize the ADC buffer
    for (int i = 0; i < ADC_SAMPLE_SIZE; i++) {
        adcBuffer[i] = 0;
    }
    
    // Start the timer
    TMR2_StartTimer();
}

void adc_control_isr_handler(void) {
    
    // Static variables are initialized to zero at the start-up
    static uint8_t index;
    // Get the ADC reading
    // The ADC channel is selected elsewhere
    adcBuffer[index] = ADC_GetConversionResult();
    
    // Deal with the index
    if (++index >= ADC_SAMPLE_SIZE) {
        index = 0;
    }
/*    
    // This is for debugging, LED heartbeat
    static uint16_t i;    
    if (++i >= 500) {
        toggle_green_led();
        i = 0;
    }
*/
}