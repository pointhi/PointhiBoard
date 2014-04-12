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

unsigned char I2cRegisterIndex = 0;
unsigned char I2cInterruptFrameIndex = 0;
unsigned char I2cInterruptI2cAdress = 0;

void I2cInit() {
    // Set I2C-Adress
    SSPADD = I2C_DEFAULT_ADRESS; 

//    IoSetPortBTris(0x00);
//    IoSetPortB(I2cRegisterIndex);

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
        switch(I2cRegisterIndex) {
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
                switch(I2cRegisterIndex) {
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

//    IoSetPortB(I2cRegisterIndex);
}