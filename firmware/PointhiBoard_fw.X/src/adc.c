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

#define ADC_ARRAY_ELEMENTS 10

unsigned char AdcInterruptCounter = 0;
unsigned int AdcArray[ADC_ARRAY_ELEMENTS];

void AdcInit() {
    AdcSetPin(ADC_PORT_VCC);

    ADCON1 = 0x00;
    // Using Voltage-Referece
    ADCON1bits.VCFG1 = 1; // Vss
    //ADCON1bits.VCFG0 = 1; // Vdd

    ADCON1 |= 0x08; // Enable AN0-AN6

    ADCON2 = 0x00;
    ADCON2bits.ADFM = 1; // Right justified
    ADCON2 |= 0x02; // 32 Tosc

    ADCON2 |= 0x1C; // 20TAD    openpoint todo

    ADCON0bits.ADON = 1; // Enable ADC

    // Set Start-Values
    AdcInterruptCounter = 0;
    AdcSetPin(ADC_PORT_VCC);

    for(char i=0; i<ADC_ARRAY_ELEMENTS; i++) {
        AdcSetValue(i,0);
    }
}

inline unsigned int AdcRead() {
    return ((ADRESH << 8) | ADRESL);
}

inline void AdcSetPin(const unsigned char _AdcPort) {
    ADCON0 &= 0x03;
    ADCON0 |= _AdcPort << 2;
}

void AdcSetMpxPin(const unsigned char _MpxPin) {
    o_ADC_MPX_INH = 1;  // Dissable MPX
    o_ADC_MPX_A = _MpxPin & 0x01;    // Set Port 1
    o_ADC_MPX_B = (_MpxPin & 0x02) >> 1;
    o_ADC_MPX_INH = 0;  // Enable
}

void AdcSetValue(const unsigned char _id, const unsigned int _value) {
    if(_id < ADC_ARRAY_ELEMENTS) {
        AdcArray[_id] = _value;
    }
}

unsigned int AdcGetValue(const unsigned char _id) {
    if(_id < ADC_ARRAY_ELEMENTS) {
        return AdcArray[_id];
    } else {
        return 0;
    }
}

unsigned int AdcConvertToVoltage(const unsigned int _AdcValue, const float _multiplier) {
    return (unsigned int)((float)(5000./1024. * (float)_AdcValue) * _multiplier);
}

inline void AdcInterrupt() {
    // To Prevent Gabage, 2. ADC-Querrys are done for each ADC-Port. The first is thrown away, the second is used.

    // If AdcInterruptCounter is a odd Value, Read Value and push it into right array element
    if(AdcInterruptCounter % 2) {
        unsigned int rawAdcVoltage = AdcRead();
        if(AdcInterruptCounter == ADC_ARRAY_VCC*2+1) {
            // Get VCC-ADC-Value
            unsigned int adcVoltageVcc = AdcConvertToVoltage(rawAdcVoltage,ADC_MULTIPLIER_VCC);
            AdcSetValue(ADC_ARRAY_VCC,adcVoltageVcc);
            AdcSetPin(ADC_PORT_5V);
        } else if(AdcInterruptCounter == ADC_ARRAY_5V*2+1) {
            // Get +5V-ADC-Value
            unsigned int adcVoltage5v = AdcConvertToVoltage(rawAdcVoltage,ADC_MULTIPLIER_5V);
            AdcSetValue(ADC_ARRAY_5V,adcVoltage5v);
            AdcSetPin(ADC_PORT_MPX_Y);
            AdcSetMpxPin(MPX_PIN_1);
        } else if (AdcInterruptCounter >= ADC_ARRAY_MPX_Y*2+1 && AdcInterruptCounter < ADC_ARRAY_MPX_X*2+1){
            // Get ADC-MPX-Y-Values
            /* AI-0 = Y1
             * AI-1 = Y3
             * AI-2 = Y2
             * AI-3 = Y0
             */
            unsigned int adcVoltageMpxY = AdcConvertToVoltage(rawAdcVoltage,ADC_MULTIPLIER_MPX);
            if(AdcInterruptCounter == ADC_ARRAY_MPX_Y*2+1) {
                // AI-0
                AdcSetValue(ADC_ARRAY_MPX_Y,adcVoltageMpxY);
                AdcSetMpxPin(MPX_PIN_3);
            } else if(AdcInterruptCounter == ADC_ARRAY_MPX_Y*2+3) {
                // AI-1
                AdcSetValue(ADC_ARRAY_MPX_Y+1,adcVoltageMpxY);
                AdcSetMpxPin(MPX_PIN_2);
            } else if(AdcInterruptCounter == ADC_ARRAY_MPX_Y*2+5) {
                // AI-2
                AdcSetValue(ADC_ARRAY_MPX_Y+2,adcVoltageMpxY);
                AdcSetMpxPin(MPX_PIN_0);
            } else {
                // AI-3
                AdcSetValue(ADC_ARRAY_MPX_Y+3,adcVoltageMpxY);
                AdcSetPin(ADC_PORT_MPX_X);
                AdcSetMpxPin(MPX_PIN_0);
            }
        } else {
            // Get ADC-MPX-X-Values
            /* AI-4 = X0
             * AI-5 = X3
             * AI-6 = X2
             * AI-7 = X1
             */
            unsigned int adcVoltageMpxX = AdcConvertToVoltage(rawAdcVoltage,ADC_MULTIPLIER_MPX);

            if(AdcInterruptCounter == ADC_ARRAY_MPX_X*2+1) {
                // AI-4
                AdcSetValue(ADC_ARRAY_MPX_X,adcVoltageMpxX);
                AdcSetMpxPin(MPX_PIN_3);
            } else if(AdcInterruptCounter == ADC_ARRAY_MPX_X*2+3) {
                // AI-5
                AdcSetValue(ADC_ARRAY_MPX_X+1,adcVoltageMpxX);
                AdcSetMpxPin(MPX_PIN_2);
            } else if(AdcInterruptCounter == ADC_ARRAY_MPX_X*2+5) {
                // AI-6
                AdcSetValue(ADC_ARRAY_MPX_X+3,adcVoltageMpxX);
                AdcSetMpxPin(MPX_PIN_0);
            } else {
                // AI-7
                AdcSetValue(ADC_ARRAY_MPX_X+4,adcVoltageMpxX);
                AdcSetPin(ADC_PORT_VCC);
            }
        }
    }
    // Gabage-ADC-Run
    else {
    }

    AdcInterruptCounter ++;
    if(AdcInterruptCounter >= ADC_ARRAY_ELEMENTS*2) {
        AdcInterruptCounter = 0;
    }

    ADCON0bits.GO_nDONE = 1; // Start ADC
}