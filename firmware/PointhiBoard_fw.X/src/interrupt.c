/**
 * @file interrupt.c
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include <pic18.h>

#include "interrupt.h"
#include "io.h"
#include "adc.h"
#include "i2c.h"
#include "define.h"

// Forward Declarations
void InterruptInitTimer0();
void InterruptInitAdc();
void InterruptInitI2C();
void InterruptOfTimer0();

void InterruptInit() {
    InterruptInitTimer0();
    InterruptInitAdc();
    InterruptInitI2C();
    
    PEIE = 1; // Aktiviere Pheripherale Interrupts
    IPEN    = 1;    // Aktiviere Prioritäten
    GIE = 1; // Aktiviere Globale Interrupt
}

void InterruptInitTimer0() {
    // Timer0 Registers:// 16-Bit Mode; Prescaler=1:4; TMRH Preset=B1; TMRL Preset=E0; Freq=50,00Hz; Period=20.000.000 ns
    T0CON, TMR0ON = 1; // Timer0 On/Off Control bit:1=Enables Timer0 / 0=Stops Timer0
    T0CON, T08BIT = 0; // Timer0 8-bit/16-bit Control bit: 1=8-bit timer/counter / 0=16-bit timer/counter
    T0CON, T0CS = 0; // TMR0 Clock Source Select bit: 0=Internal Clock (CLKO) / 1=Transition on T0CKI pin
    T0CON, T0SE = 0; // TMR0 Source Edge Select bit: 0=low/high / 1=high/low
    T0CON, PSA = 0; // Prescaler Assignment bit: 0=Prescaler is assigned; 1=NOT assigned/bypassed
    T0CON, T0PS2 = 0; // bits 2-0  PS2:PS0: Prescaler Select bits
    T0CON, T0PS1 = 0;
    T0CON, T0PS0 = 1;

    TMR0IP = 1; // Timer 0 ... High Priority
    TMR0IE = 1; // Activate Interrupt for Timer0
}

void InterruptInitAdc() {
    PIE1bits.ADIE = 1; // Aktiviere Interrupt für ADC
    IPR1bits.ADIP = 0; // Low Priority

    // Start Endless ADC-Call
    ADCON0bits.GO_nDONE = 1; // Start ADC
}

void InterruptInitI2C() {
    PIE1bits.SSPIE = 1; // Aktiviere Interrupt für MSSP-Modul
    IPR1bits.SSPIP = 0; // Low Priority
}

void InterruptOfTimer0() {
    IoUpdateLedOutput();
    IoGotoNextMacroBit();
}

void interrupt tc_int(void) {
    if (TMR0IF == 1) // Interrupt, Timer0
    {
        // Config 50Hz Mode
        TMR0H = 0xB1; // preset for Timer0 MSB register
        TMR0L = 0xE0; // preset for Timer0 LSB register
        TMR0IF = 0;
        InterruptOfTimer0();
    }
}

void interrupt low_priority tc_clr(void) {
    if (PIR1bits.SSPIF == 1 && PIE1bits.SSPIE == 1) // I2C-Interrupt    // Help, when Chip error
    {
        PIR1bits.SSPIF = 0;
        I2cInterrupt();
    }
    if (PIR1bits.ADIF == 1 && PIE1bits.ADIE == 1) // ADC-Interrupt
    {
        PIR1bits.ADIF = 0;
        AdcInterrupt();
    }
}