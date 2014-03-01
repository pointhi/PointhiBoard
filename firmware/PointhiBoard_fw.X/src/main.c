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


    while (1) {
//        AdcSetPin(ADC_PORT_5V);
//        ADCON0bits.GO_nDONE = 1; // Start ADC
//        __delay_ms(50);
//        if(AdcConvertToVoltage(AdcRead(),ADC_MULTIPLIER_5V) <= 4994) {
//            IoSetLedInfo(LED_OFF);
//            IoSetLedStat(LED_OFF);
//        } else if(AdcConvertToVoltage(AdcRead(),ADC_MULTIPLIER_5V) <= 4995) {
//            IoSetLedInfo(LED_ON);
//            IoSetLedStat(LED_OFF);
//        } else if(AdcConvertToVoltage(AdcRead(),ADC_MULTIPLIER_5V) <= 4996) {
//            IoSetLedInfo(LED_OFF);
//            IoSetLedStat(LED_ON);
//        } else {
//            IoSetLedInfo(LED_ON);
//            IoSetLedStat(LED_ON);
//        }
//        IoSetLedInfo(LED_PEAK_SLOW);
    }
}

