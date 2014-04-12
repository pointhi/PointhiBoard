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
inline void AdcInterrupt();

inline unsigned int AdcRead();
inline void AdcSetPin(const unsigned char _AdcPort);
void AdcSetMpxPin(const unsigned char _MpxPin);

void AdcSetValue(const unsigned char _id, const unsigned int _value);
unsigned int AdcGetValue(const unsigned char _id);
unsigned char AdcGetValueHighByte(const unsigned char _id);
unsigned char AdcGetValueLowByte(const unsigned char _id);

unsigned int AdcConvertToVoltage(const unsigned int _AdcValue, const float _multiplier);

#endif	/* ADC_H */

