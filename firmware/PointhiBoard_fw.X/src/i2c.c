/**
 * @file i2c.c
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include <plib/i2c.h>   // I2C
//#include <plib/EEP.h>   // EEprom

#include "i2c.h"
#include "define.h"
#include "io.h"
#include "adc.h"

unsigned char I2cRegisterIndex = 0;
unsigned char I2cInterruptFrameIndex = 0;
unsigned char I2cInterruptI2cAdress = 0;

void I2cInit() {
    // Set I2C-Adress
    SSPADD = I2C_DEFAULT_ADRESS; 

    // Clear SSPSTAT
    SSPSTAT = 0x00;

    SSPSTATbits.SMP = 1;        // Slew Rate Control disabled for Standard Speed mode
    //    SSPSTATbits.CKE = 1;        // Enable SMBus specific inputs

    // I2C Slave mode, 7-bit adress
    SSPCON1 = 0x06; 

    // Clear SSPCON2
    SSPCON2 = 0x00;
    
    // Enable Clock stretching
    SSPCON2bits.SEN = 1;

    // Enable interrupt on general adress
    //SSPCON2bits.GCEN = 1;

    // Enables I2C Port
    SSPCON1bits.SSPEN = 1; 
}

inline void I2cInterrupt() {
    // Workaround, to decrement Register-Index at next I2c-Request if necessary
    static unsigned char DecrementI2cRegisterIndex = 0;

    if (!SSPSTATbits.D_NOT_A) {
        // Last recived Byte was Adress
        // Clear BF and get I2c-Adress
        I2cInterruptI2cAdress = SSPBUF;
        I2cInterruptFrameIndex = 0;
        if(DecrementI2cRegisterIndex) {
            I2cRegisterIndex --;
            DecrementI2cRegisterIndex = 0;;
        }
    } else {
        // Last recived Byte was Data
        I2cInterruptFrameIndex ++;
    }

//    if(SSPCON1bits.SSPOV ) {
//        IoSetLedInfo(LED_BLINK_SLOW);
//        SSPCON1bits.SSPOV = 0;
//    }
//
//    if(SSPCON1bits.WCOL) {
//        IoSetLedStat(LED_BLINK_SLOW);
//        SSPCON1bits.WCOL = 0;
//    }

    if (SSPSTATbits.R_NOT_W) {
        // Master Read Data from Slave
        
        // Perform Action depending on RegisterIndex
        /* 0x01     TRISB
         * 0x0F     Read PORTB
         * 0x10     ADC - 0 VOLTAGE-HIGH-BYTE
         * 0x11     ADC - 0 VOLTAGE-LOW-BYTE
         * 0x12     ADC - 1 VOLTAGE-HIGH-BYTE
         * 0x13     ADC - 1 VOLTAGE-LOW-BYTE
         * 0x14     ADC - 2 VOLTAGE-HIGH-BYTE
         * 0x15     ADC - 2 VOLTAGE-LOW-BYTE
         * 0x16     ADC - 3 VOLTAGE-HIGH-BYTE
         * 0x17     ADC - 3 VOLTAGE-LOW-BYTE
         * 0x18     ADC - 4 VOLTAGE-HIGH-BYTE
         * 0x19     ADC - 4 VOLTAGE-LOW-BYTE
         * 0x1A     ADC - 5 VOLTAGE-HIGH-BYTE
         * 0x1B     ADC - 5 VOLTAGE-LOW-BYTE
         * 0x1C     ADC - 6 VOLTAGE-HIGH-BYTE
         * 0x1D     ADC - 6 VOLTAGE-LOW-BYTE
         * 0x1E     ADC - 7 VOLTAGE-HIGH-BYTE
         * 0x1F     ADC - 7 VOLTAGE-LOW-BYTE
         * 0x20     ADC - VCC VOLTAGE-HIGH-BYTE
         * 0x21     ADC - VCC VOLTAGE-LOW-BYTE
         * 0x22     ADC - +5V VOLTAGE-HIGH-BYTE
         * 0x23     ADC - +5V VOLTAGE-LOW-BYTE
         */
        switch(I2cRegisterIndex) {
            case 0x01:
                SSPBUF = IoGetPortBTris();
                break;
                
            case 0x0F:
                SSPBUF = IoGetPortB();
                break;

            case 0x10:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI);
                break;

            case 0x11:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI);
                break;

            case 0x12:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI+1);
                break;

            case 0x13:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI+1);
                break;

            case 0x14:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI+2);
                break;

            case 0x15:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI+2);
                break;

            case 0x16:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI+3);
                break;

            case 0x17:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI+3);
                break;

            case 0x18:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI+4);
                break;

            case 0x19:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI+4);
                break;

            case 0x1A:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI+5);
                break;

            case 0x1B:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI+5);
                break;

            case 0x1C:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI+6);
                break;

            case 0x1D:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI+6);
                break;

            case 0x1E:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_AI+7);
                break;

            case 0x1F:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_AI+7);
                break;

            case 0x20:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_VCC);
                break;

            case 0x21:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_VCC);
                break;

            case 0x22:
                SSPBUF = AdcGetValueHighByte(ADC_ARRAY_5V);
                break;

            case 0x23:
                SSPBUF = AdcGetValueLowByte(ADC_ARRAY_5V);
                break;

            default:
                SSPBUF = I2cRegisterIndex;
                break;
        }

        // Set next Register-Index
        I2cRegisterIndex ++;
        // Workaround, to decrement the last increment of RegisterIndex
        DecrementI2cRegisterIndex = 1;

        // Release Clock
        SSPCON1bits.CKP = 1;
    }
    else {
        // Master Write Data from Slave

        if (SSPSTATbits.D_NOT_A) {
            // Last recived Byte was Data
            if(I2cInterruptFrameIndex == 1) {
                // Update Register Index
                I2cRegisterIndex = SSPBUF; 
            } else {
                
                // Perform Action depending on RegisterIndex
                /* 0x01     Set TRISB
                 * 0x0F     Set PORTB
                 */
                switch(I2cRegisterIndex) {
                    case 0x01:
                        IoSetPortBTris(SSPBUF);
                        break;

                    case 0x0F:
                        IoSetPortB(SSPBUF);
                        break;

                    default: {
                        unsigned char I2cDelRegister = SSPBUF;
                        }
                        break;
                }

                // Set next Register-Index
                I2cRegisterIndex ++;
            }
        }

        // Release Clock
        SSPCON1bits.CKP = 1;
    }
}