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

    PbPrintStatus();

    printf("Close I2c-Connection\n");
    PbI2cClose();

    return (EXIT_SUCCESS);
}

