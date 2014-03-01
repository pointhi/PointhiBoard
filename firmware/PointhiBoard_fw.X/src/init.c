/**
 * @file init.c
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include <pic18.h>

#include "init.h"
#include "define.h"
#include "interrupt.h"
#include "io.h"
#include "adc.h"
#include "i2c.h"

// Forward declarations
void InitOsc();
void InitPort();

void InitSystem() {
    // General init
    InitOsc();
    InitPort();

    // Peripheral init
    AdcInit();
    I2cInit();

    // Interrupt init
    InterruptInit();
}

void InitOsc() {
#ifdef __OSC_INTOSC          // PLL Disabled, 8MHz
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCTUNEbits.PLLEN = 0;
#endif
}

void InitPort() {

    TRISA = 0xFF; // 1... Input
    TRISB = 0xFF; // 0... Output
    TRISC = 0xFF;
    TRISD = 0b00111100;
    TRISE = 0x0F;

    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
}

void InitStartSequence() {

    IoSetLedStat(LED_ON);
    IoSetLedInfo(LED_ON);

    for (int i = 0; i < 5; i++) {
        __delay_ms(50);
    }
    IoSetFet5v(FET_ON);
    for (int i = 0; i < 10; i++) {
        __delay_ms(50);
    }
    IoSetFetVcc(FET_ON);

    IoSetLedStat(LED_OFF);
    IoSetLedInfo(LED_OFF);
}