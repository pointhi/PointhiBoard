/**
 * @file    PointhiBoard.h
 *
 * @author  thomas
 *
 * @date    8. May 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#ifndef POINTHIBOARD_H
#define	POINTHIBOARD_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _PB_REGISTER_S_TRISB    0x01
#define _PB_REGISTER_S_PORTB    0x0F

#define _PB_REGISTER_G_TRISB    0x01
#define _PB_REGISTER_G_PORTB    0x0F

#define _PB_REGISTER_G_ADC0_H   0x10
#define _PB_REGISTER_G_ADC0_L   0x11
#define _PB_REGISTER_G_ADC1_H   0x12
#define _PB_REGISTER_G_ADC1_L   0x13
#define _PB_REGISTER_G_ADC2_H   0x14
#define _PB_REGISTER_G_ADC2_L   0x15
#define _PB_REGISTER_G_ADC3_H   0x16
#define _PB_REGISTER_G_ADC3_L   0x17
#define _PB_REGISTER_G_ADC4_H   0x18
#define _PB_REGISTER_G_ADC4_L   0x19
#define _PB_REGISTER_G_ADC5_H   0x1A
#define _PB_REGISTER_G_ADC5_L   0x1B
#define _PB_REGISTER_G_ADC6_H   0x1C
#define _PB_REGISTER_G_ADC6_L   0x1D
#define _PB_REGISTER_G_ADC7_H   0x1E
#define _PB_REGISTER_G_ADC7_L   0x1F

#define _PB_REGISTER_G_VCC_H    0x20
#define _PB_REGISTER_G_VCC_L    0x21
#define _PB_REGISTER_G_5V_H     0x22
#define _PB_REGISTER_G_5V_L     0x23

#define _PB_ADC0                _PB_REGISTER_G_ADC0_H
#define _PB_ADC1                _PB_REGISTER_G_ADC1_H
#define _PB_ADC2                _PB_REGISTER_G_ADC2_H
#define _PB_ADC3                _PB_REGISTER_G_ADC3_H
#define _PB_ADC4                _PB_REGISTER_G_ADC4_H
#define _PB_ADC5                _PB_REGISTER_G_ADC5_H
#define _PB_ADC6                _PB_REGISTER_G_ADC6_H
#define _PB_ADC7                _PB_REGISTER_G_ADC7_H
#define _PB_ADC_VCC             _PB_REGISTER_G_VCC_H
#define _PB_ADC_5V              _PB_REGISTER_G_5V_H

    /**
     * @brief
     *
     * @return -1...Setting Adress failed
     */
    signed int PbI2cOpen();

    /**
     * @brief
     *
     * @return
     */
    signed int PbI2cConnect();

    /**
     * @brief
     *
     * @return
     */
    signed int PbI2cClose();

    /**
     * @brief
     *
     * @param _i2cAdress
     */
    void PbI2cSetAdress(unsigned int _i2cAdress);

    /**
     *
     * @return
     */
    unsigned int PbI2cGetAdress();

    /**
     *
     * @param _i2cRegisterId
     * @param _i2cRegisterValue
     */
    void PbI2cSetRegister(unsigned char _i2cRegisterId, unsigned char _i2cRegisterValue);

    /**
     *
     * @param _i2cRegisterId
     * @return
     */
    unsigned char PbI2cGetRegister(unsigned char _i2cRegisterId);

    unsigned int PbI2cGetADC(unsigned char _i2cAdcHighRegisterId);

    void PbPrintStatus();

#ifdef	__cplusplus
}
#endif

#endif	/* POINTHIBOARD_H */

