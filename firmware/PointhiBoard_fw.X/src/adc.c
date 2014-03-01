/**
 * @file adc.c
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include <pic18.h>

#include "adc.h"
#include "define.h"

void AdcInit() {
    AdcSetPin(ADC_PORT_5V);

    ADCON1 = 0x00;
    // Using Voltage-Referece
    ADCON1bits.VCFG1 = 1; // Vss
    ADCON1bits.VCFG0 = 1; // Vdd

    ADCON1 |= 0x09; // Enable AN0-AN5

    ADCON2 = 0x00;
    ADCON2bits.ADFM = 1; // Right justified
    ADCON2 |= 0x02; // 32 Tosc

    ADCON2 |= 0x1C; // 20TAD    openpoint todo

    ADCON0bits.ADON = 1; // Enable ADC

    //    ADCON0bits.GO_nDONE = 1;   // starte ADC
}

unsigned int AdcRead() {
    return ((ADRESH * 256) + ADRESL); // &(ADRESL/64)
}

void AdcSetPin(unsigned char _AdcPort) {
    ADCON0 &= 0x03;
    ADCON0 |= _AdcPort << 2;
}

unsigned int AdcConvertToVoltage(unsigned int _AdcValue, float _multiplier) {
    return (unsigned int)((float)(5000./2048. * (float)_AdcValue) * _multiplier);
}

void AdcInterrupt() {

    if (!ADCON0bits.GO_nDONE) // Adc-Converter Finished
    {
        //            RcjAdcPinValue[RcjAdcPinSelect] = RcjAdcRead();
        //
        //            RcjAdcPinSelect ++;
        //            if(RcjAdcPinSelect>=RCJ_ADC_PIN_VALUE)
        //                {
        //                RcjAdcPinSelect = 0;
        //                }
        //            RcjAdcSetPort(RcjAdcPinSelect);
        //
        //            ADCON0bits.GO_nDONE = 1;   // starte ADC
    }
}