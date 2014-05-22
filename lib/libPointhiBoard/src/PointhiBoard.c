/**
 * @file    PointhiBoard.c
 *
 * @author  thomas
 *
 * @date    8. May 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include "PointhiBoard.h"

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static unsigned int g_PbI2cAdress = 0x60;
static signed int g_PbI2cFd = -1;

signed int PbI2cOpen() {
    // Open File
    if ((g_PbI2cFd = open("/dev/i2c-1", O_RDWR)) < 0) {
        printf("ERROR: Failed to open I2C-Device /dev/i2c-1\n");
        return -1;
    }
    return 0;
}

signed int PbI2cConnect() {
    if (g_PbI2cFd < 0) {
        printf("ERROR: No device Opened\n");
        return -1;
    } else {
        return ioctl(g_PbI2cFd, I2C_SLAVE, g_PbI2cAdress);
    }
}

signed int PbI2cClose() {
    close(g_PbI2cFd);
    return 0;
}

void PbI2cSetAdress(unsigned int _i2cAdress) {
    g_PbI2cAdress = _i2cAdress & 0xFFFE;
}

unsigned int PbI2cGetAdress() {
    return g_PbI2cAdress;
}

void PbI2cSetRegister(unsigned char _i2cRegisterId, unsigned char _i2cRegisterValue) {
    unsigned char buffer[2];
    buffer[0] = _i2cRegisterId;
    buffer[1] = _i2cRegisterValue;

    if (g_PbI2cAdress >= 0) {
        if (write(g_PbI2cFd, &buffer, 2) != 2) {
            printf("ERROR: Failed to write to 0x%X\n", g_PbI2cAdress);
            return;
        }
    }
}

unsigned char PbI2cGetRegister(unsigned char _i2cRegisterId) {
    if (g_PbI2cAdress < 0) {
        return 0;
    } else {

        if (write(g_PbI2cFd, &_i2cRegisterId, 1) != 1) {
            printf("ERROR: Failed to write to 0x%X\n", g_PbI2cAdress);
            return 0;
        }

        unsigned char I2cReadData = 0;

        if (read(g_PbI2cFd, &I2cReadData, 1) != 1) {
            printf("ERROR: Failed to read from 0x%X\n", g_PbI2cAdress);
            return 0;
        }
        return I2cReadData;
    }
}

unsigned int PbI2cGetADC(unsigned char _i2cAdcHighRegisterId) {
    if (g_PbI2cAdress < 0) {
        return 0;
    } else {

        if (write(g_PbI2cFd, &_i2cAdcHighRegisterId, 1) != 1) {
            printf("ERROR: Failed to write to 0x%X\n", g_PbI2cAdress);
            return 0;
        }

        unsigned char I2cReadData[2];

        if (read(g_PbI2cFd, &I2cReadData, 2) != 2) {
            printf("ERROR: Failed to read from 0x%X\n", g_PbI2cAdress);
            return 0;
        }

        unsigned int voltage = I2cReadData[0] << 8 | I2cReadData[1];

        return voltage;
    }
}

void PbPrintStatus() {
    printf("   STATUS\n");
    printf("############\n\n");
    unsigned char i = 0;
    for (i = 0; i < 8; i++) {
        printf("ADC%d = %dmV\n", i, PbI2cGetADC(_PB_ADC0 + i * 2));
    }

    printf("\nADC-VCC = %dmV\n", PbI2cGetADC(_PB_ADC_VCC));
    printf("ADC-+5V = %dmV\n\n", PbI2cGetADC(_PB_ADC_5V));

    printf("TRISB = 0x%X\n", PbI2cGetRegister(_PB_REGISTER_G_TRISB));
    printf("PORTB = 0x%X\n\n", PbI2cGetRegister(_PB_REGISTER_G_PORTB));

    printf("############\n\n");
}