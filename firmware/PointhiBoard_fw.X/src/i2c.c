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

void I2cInit() {

    SSPADD = I2C_DEFAULT_ADRESS; // Set Adress

    SSPSTAT = 0x00;

    //    SSPSTATbits.SMP = 1;        // Slew Rate Control disabled for Standard Speed mode
    //    SSPSTATbits.CKE = 1;        // Enable SMBus specific inputs


    SSPCON1 = 0x00;
    //    SSPCON1 &= 0x2F;

    //    SSPCON1 |= 0x0E;            // Slave mode, 7-bit adress with Start and Stop bit interrupts enabled
    SSPCON1 |= 0x06; // Slave mode, 7-bit adress

    SSPCON1bits.SSPEN = 1; // Enables the mssp Port

    SSPCON2 = 0x00;

    //    SSPCON2bits.GCEN = 1;       // Enable interrupt on general adress
    //    SSPCON2bits.SEN = 1;        // Clock Streching is enabled for transmit and receive
}

void I2cInterrupt() {
    if (SSPSTATbits.BF) // New Byte recive
    {
        SSPSTATbits.BF = 0;
        if (!SSPSTATbits.R_NOT_W) // Master Write Data
        {
            IoSetLedStat(LED_ON);
            if (SSPSTATbits.D_NOT_A) // Last recived Byte was Data
            {
                unsigned char I2cHelp = SSPBUF;
                SSPBUF = I2cHelp;
                //                switch(I2cRegisterSelect)
                //                    {
                ////                    case 0:
                ////                        break;
                //                    case 1: // 1. Engine
                //                        if(I2cHelp == 128)
                //                            {
                //                            Engine1Stop();
                //                            }
                //                        else if(I2cHelp > 128)
                //                            {
                //                            Engine1Forward();
                //                            Engine1Pwm((I2cHelp-128)*2);
                //                            }
                //                        else
                //                            {
                //
                //                            Engine1Backward();
                //                            Engine1Pwm((128-I2cHelp)*2);
                //                            }
                //                        break;
                //                    case 2:
                //                        break;
                //                    case 3: // 2. Engine
                //                        if(I2cHelp == 128)
                //                            {
                //                            Engine2Stop();
                //                            }
                //                        else if(I2cHelp > 128)
                //                            {
                //                            Engine2Forward();
                //                            Engine2Pwm((I2cHelp-128)*2);
                //                            }
                //                        else
                //                            {
                //                            Engine2Backward();
                //                            Engine2Pwm((128-I2cHelp)*2);
                //                            }
                //                        break;
                //                    case 4:
                //                        break;
                //                    default:
                //                        break;
                //                    }
                //                I2cRegisterSelect ++;
            } else // Last recived Byte was Adress
            {
                //                I2cRegisterSelect = SSPBUF; // Update Register Select
                //                I2cRegisterSelect = 0;
            }

            SSPCON1bits.CKP = 1;
        } else // Master Request Data
        {
            IoSetLedInfo(LED_ON);
            if (!SSPSTATbits.D_NOT_A) // Last recived Byte was Adress
            {
                //                I2cRegisterSelect = 0; // Update Register Select
            }
            SSPCON1bits.SSPOV = 0;
            SSPCON1bits.WCOL = 0;
            //            I2cHelp = SSPBUF;
            //                I2cRegisterSelect = 0xFF;
            //                SSPBUF = I2cRegisterSelect;

            //            switch(I2cRegisterSelect)
            //                {
            //                case 0:
            SSPBUF = 0x00;
            //                    break;
            //                case 1:
            //
            //
            //                    break;
            //
            //                case 2:
            //
            //
            //                    break;
            //
            //                default:
            //                    SSPBUF = 0x00;
            //                    break;
            //                }

            //            I2cRegisterSelect ++;
            SSPCON1bits.CKP = 1;
        }
    }
    SSPCON1bits.CKP = 1;
//    PIR1bits.SSPIF = 0; // Reset Interrupt-Byte
}