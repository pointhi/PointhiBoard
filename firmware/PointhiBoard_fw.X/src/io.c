/**
 * @file io.c
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include <pic18.h>

#include "io.h"
#include "define.h"

unsigned char LedInfoMacro = LED_OFF;
unsigned char LedStatMacro = LED_OFF;

unsigned char LedActiveMacroBit = 0x01;

void IoSetLedInfo(unsigned char _ledMacro) {
    LedInfoMacro = _ledMacro;
}

void IoSetLedStat(unsigned char _ledMacro) {
    LedStatMacro = _ledMacro;
}

void IoGotoNextMacroBit() {
    LedActiveMacroBit = LedActiveMacroBit << 1;
    if (!LedActiveMacroBit) {
        LedActiveMacroBit = 0x01;
    }
}

void IoUpdateLedOutput() {

    if (LedActiveMacroBit & LedStatMacro) {
        o_LED_STAT = 1;
    } else {
        o_LED_STAT = 0;
    }

    if (LedActiveMacroBit & LedInfoMacro) {
        o_LED_INFO = 1;
    } else {
        o_LED_INFO = 0;
    }
}

void IoSetFet5v(unsigned char _value) {
    if (_value) {
        o_FET_5V = 1;
    } else {
        o_FET_5V = 0;
    }
}

void IoSetFetVcc(unsigned char _value) {
        if (_value) {
        o_FET_VCC = 1;
    } else {
        o_FET_VCC = 0;
    }
}