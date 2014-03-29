/**
 * @file main.c
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include <pic18.h>

#include "define.h"
#include "init.h"
#include "io.h"

#include "adc.h"

// Setting Config-Bits
#ifdef __OSC_INTOSC
    #pragma config IESO = OFF, OSC = INTIO67, FCMEN = OFF               // CONFIG 1H        // Internal Oscilator
#else
    #pragma config IESO = OFF, OSC = HS, FCMEN = OFF                    // CONFIG 1H        // External Oscillator
#endif
#pragma config BOREN = OFF, PWRT = OFF                                  // CONFIG 2L
#pragma config WDT = OFF                                                // CONFIG 2H
#pragma config CCP2MX = PORTC, PBADEN = OFF, LPT1OSC = OFF, MCLRE = OFF // CONFIG 3H
#pragma config STVREN = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF        // CONFIG 4L
#pragma config CP0 = OFF, CP1 = OFF                                     // CONFIG 5L
#pragma config CPD = OFF, CPB = OFF                                     // CONFIG 5H
#pragma config WRT0 = OFF, WRT1 = OFF                                   // CONFIG 6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                       // CONFIG 6H
#pragma config EBTR0 = OFF, EBTR1 = OFF                                 // CONFIG 7L
#pragma config EBTRB = OFF                                              // CONFIG 7H

// Main-Function

void main() {

    InitSystem();

    InitStartSequence();

    TRISB = 0x00;

    while (1) {

        //LATB = ((int)((AdcGetValue(ADC_ARRAY_VCC)/ADC_MULTIPLIER_VCC)*1024./5000.) >> 2) & 0xFF;

        LATB = ((int)((AdcGetValue(ADC_ARRAY_AI)/ADC_MULTIPLIER_MPX)*1024./5000.) >> 2) & 0xFF;

        if(AdcGetValue(ADC_ARRAY_VCC) <= 7000) {
            IoSetLedInfo(LED_OFF);
            IoSetLedStat(LED_OFF);
        } else if(AdcGetValue(ADC_ARRAY_VCC) <= 10000) {
            IoSetLedInfo(LED_ON);
            IoSetLedStat(LED_OFF);
        } else if(AdcGetValue(ADC_ARRAY_VCC) <= 12000) {
            IoSetLedInfo(LED_OFF);
            IoSetLedStat(LED_ON);
        } else {
            IoSetLedInfo(LED_ON);
            IoSetLedStat(LED_ON);
        }
    }
}

