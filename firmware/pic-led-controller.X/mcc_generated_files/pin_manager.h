/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16LF1709
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set sensor aliases
#define sensor_TRIS                 TRISCbits.TRISC1
#define sensor_LAT                  LATCbits.LATC1
#define sensor_PORT                 PORTCbits.RC1
#define sensor_WPU                  WPUCbits.WPUC1
#define sensor_OD                   ODCONCbits.ODC1
#define sensor_ANS                  ANSELCbits.ANSC1
#define sensor_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define sensor_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define sensor_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define sensor_GetValue()           PORTCbits.RC1
#define sensor_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define sensor_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define sensor_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define sensor_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define sensor_SetPushPull()        do { ODCONCbits.ODC1 = 0; } while(0)
#define sensor_SetOpenDrain()       do { ODCONCbits.ODC1 = 1; } while(0)
#define sensor_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define sensor_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set vMeas aliases
#define vMeas_TRIS                 TRISCbits.TRISC3
#define vMeas_LAT                  LATCbits.LATC3
#define vMeas_PORT                 PORTCbits.RC3
#define vMeas_WPU                  WPUCbits.WPUC3
#define vMeas_OD                   ODCONCbits.ODC3
#define vMeas_ANS                  ANSELCbits.ANSC3
#define vMeas_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define vMeas_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define vMeas_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define vMeas_GetValue()           PORTCbits.RC3
#define vMeas_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define vMeas_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define vMeas_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define vMeas_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define vMeas_SetPushPull()        do { ODCONCbits.ODC3 = 0; } while(0)
#define vMeas_SetOpenDrain()       do { ODCONCbits.ODC3 = 1; } while(0)
#define vMeas_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define vMeas_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set ledRed aliases
#define ledRed_TRIS                 TRISCbits.TRISC6
#define ledRed_LAT                  LATCbits.LATC6
#define ledRed_PORT                 PORTCbits.RC6
#define ledRed_WPU                  WPUCbits.WPUC6
#define ledRed_OD                   ODCONCbits.ODC6
#define ledRed_ANS                  ANSELCbits.ANSC6
#define ledRed_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define ledRed_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define ledRed_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define ledRed_GetValue()           PORTCbits.RC6
#define ledRed_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define ledRed_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define ledRed_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define ledRed_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define ledRed_SetPushPull()        do { ODCONCbits.ODC6 = 0; } while(0)
#define ledRed_SetOpenDrain()       do { ODCONCbits.ODC6 = 1; } while(0)
#define ledRed_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define ledRed_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set ledGrn aliases
#define ledGrn_TRIS                 TRISCbits.TRISC7
#define ledGrn_LAT                  LATCbits.LATC7
#define ledGrn_PORT                 PORTCbits.RC7
#define ledGrn_WPU                  WPUCbits.WPUC7
#define ledGrn_OD                   ODCONCbits.ODC7
#define ledGrn_ANS                  ANSELCbits.ANSC7
#define ledGrn_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define ledGrn_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define ledGrn_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define ledGrn_GetValue()           PORTCbits.RC7
#define ledGrn_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define ledGrn_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define ledGrn_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define ledGrn_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define ledGrn_SetPushPull()        do { ODCONCbits.ODC7 = 0; } while(0)
#define ledGrn_SetOpenDrain()       do { ODCONCbits.ODC7 = 1; } while(0)
#define ledGrn_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define ledGrn_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/