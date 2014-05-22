/*
 * File:   main.c
 * Author: thomas
 *
 * Created on 15. Mai 2014, 10:14
 */

#include <stdio.h>
#include <stdlib.h>

#include <PointhiBoard.h>

int main(int argc, char** argv) {

    printf("Open I2c-Connection\n");
    PbI2cOpen();

    printf("Connect to Chip: 0x%X\n", PbI2cGetAdress());
    PbI2cConnect();

    printf("Set TRISB to output\n");
    PbI2cSetRegister(_PB_REGISTER_S_TRISB, 0x00);

    printf("Set PORTB output\n");
    PbI2cSetRegister(_PB_REGISTER_S_PORTB, 0x55);

    /*
        printf("Get ADC-Values\n");
        unsigned int adc_high = PbI2cGetRegister(_PB_REGISTER_G_ADC0_H);
        unsigned int adc_low = PbI2cGetRegister(_PB_REGISTER_G_ADC0_L);
        float adc = (float) ((int) (adc_low | (adc_high < 8))) / 1000.;
     */

    /*
        printf("Voltage from ADC0: %fV\n", adc);
     */

    PbPrintStatus();

    printf("Close I2c-Connection\n");
    PbI2cClose();

    return (EXIT_SUCCESS);
}

