/**
  Section: Included Files
*/
#include "leds.h"

void turn_off_red_led(void) {
    ledRed_SetLow();
}
void turn_on_red_led(void) {
    ledRed_SetHigh();
}
void toggle_red_led(void) {
    ledRed_Toggle();
}
    
void turn_off_green_led(void) {
    ledGrn_SetLow();
}
void turn_on_green_led(void) {
    ledGrn_SetHigh();
}
void toggle_green_led(void) {
    ledGrn_Toggle();
}