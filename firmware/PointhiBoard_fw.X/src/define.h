/**
 * @file define.h
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#ifndef DEFINE_H
#define	DEFINE_H

#include <pic18.h>

// Using the internal oscillator
#define __OSC_INTOSC 1

#define _XTAL_FREQ 8000000

// Pins which are used by the fet's and led's

#define o_FET_VCC               LATDbits.LATD0
#define o_FET_5V                LATDbits.LATD1
#define o_LED_STAT              LATDbits.LATD6
#define o_LED_INFO              LATDbits.LATD7

// Pins which are used by the analoge multiplexer

#define o_ADC_MPX_A             LATDbits.LATD5
#define o_ADC_MPX_B             LATDbits.LATD4
#define o_ADC_MPX_INH           LATCbits.LATC0

#define FET_OFF                 0x00
#define FET_ON                  0xFF

// Different flashing pattern for the led's

#define LED_OFF                 0x00
#define LED_ON                  0xFF
#define LED_BLINK_SLOW          0xF0
#define LED_BLINK_SLOW_INVERTED 0x0F
#define LED_BLINK_FAST          0xAA
#define LED_BLINK_FAST_INVERTED 0x55
#define LED_PEAK_SLOW           0x80
#define LED_PEAK_SLOW_INVERTED  0x08
#define LED_PEAK_FAST           0x88
#define LED_PEAK_FAST_INVERTED  0x22

// Multiplexer

#define MPX_PIN_0               0x00
#define MPX_PIN_1               0x01
#define MPX_PIN_2               0x02
#define MPX_PIN_3               0x03

// ADC-Port definitions

#define ADC_PORT_MPX_Y          0
#define ADC_PORT_MPX_X          1
#define ADC_PORT_5V             4
// Rev-1.3 manual connected!
#define ADC_PORT_VCC            5

// ADC-Array definitions

#define ADC_ARRAY_VCC           0
#define ADC_ARRAY_5V            1
#define ADC_ARRAY_MPX_Y         2
#define ADC_ARRAY_MPX_X         ADC_ARRAY_MPX_Y + 4
#define ADC_ARRAY_AI            ADC_ARRAY_MPX_Y

// Define the voltage divider on the input for the ADC

#define ADC_MULTIPLIER_MPX      1
#define ADC_MULTIPLIER_5V       2
#define ADC_MULTIPLIER_VCC      9

// I2C

#define I2C_DEFAULT_ADRESS      0xC0

#endif	/* DEFINE_H */