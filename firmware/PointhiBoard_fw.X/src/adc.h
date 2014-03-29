/**
 * @file adc.h
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#ifndef ADC_H
#define	ADC_H

void AdcInit();
void AdcInterrupt();

unsigned int AdcRead();
void AdcSetPin(unsigned char _AdcPort);
void AdcSetMpxPin(unsigned char _MpxPin);

void AdcSetValue(unsigned char _id, unsigned int _value);
unsigned int AdcGetValue(unsigned char _id);

unsigned int AdcConvertToVoltage(unsigned int _AdcValue, float _multiplier);

#endif	/* ADC_H */

