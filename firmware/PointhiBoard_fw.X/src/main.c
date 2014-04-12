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
#include "time.h"

#ifdef __TEST
    #include "test.h"
    #warning "Compiling Test-Code!"
#endif

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

#ifdef __TEST
    IoSetLedInfo(LED_BLINK_FAST);
    IoSetLedStat(LED_BLINK_FAST);
    unsigned char returnValue = TestRun();
    if(returnValue) {
        IoSetLedInfo(LED_PEAK_SLOW);
        IoSetLedStat(LED_OFF);

    } else {
        IoSetLedInfo(LED_OFF);
        IoSetLedStat(LED_ON);
    }
    
    while (1) {
    }
#endif

    while (1) {

    }
}

