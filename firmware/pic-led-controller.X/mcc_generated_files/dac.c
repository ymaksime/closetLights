/**
  DAC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    dac.c

  @Summary
    This is the generated driver implementation file for the DAC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for DAC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16LF1709
        Driver Version    :  2.10
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "dac.h"

/**
  Section: DAC APIs
*/

void DAC_Initialize(void)
{
    // DAC1EN enabled; DAC1NSS VSS; DAC1PSS FVR; DAC1OE1 disabled; DAC1OE2 disabled; 
    DAC1CON0 = 0x88;
    // DAC1R 0; 
    DAC1CON1 = 0x7D;
}

void DAC_SetOutput(uint8_t inputData)
{
    // If input value is 0, reconfigure the OP-AMP into a unity gain to make
    // sure we don't source any current the outside transistor is completely off
    if (0 == inputData) {
        OPA1CON = 0xD2;
    }
    else {
        OPA1CON = 0xC2;
    }
    DAC1CON1  = inputData;
}

uint8_t DAC_GetOutput(void)
{
    return DAC1CON1;
}
/**
 End of File
*/
