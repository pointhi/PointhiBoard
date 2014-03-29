/**
 * @file test.c
 *
 * @author thomas
 *
 * @date 29. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include "test.h"

#include <pic18.h>

#include "define.h"
#include "io.h"
#include "adc.h"
#include "time.h"

unsigned char TestRun() {
    unsigned char returnValue = 0x00;
    
    returnValue |= TestIO();

    return returnValue;
}

unsigned char TestIO() {
    TRISB = 0x00;

    for(unsigned char i=0;i<8;i++) {
        LATB = 1 << i;
        TimeWaitMs(100);

        if(AdcGetValue(ADC_ARRAY_AI+i) < 4000) {
            return 1;
        }

        for(unsigned char j=0;j<8;j++) {
            if(i != j && AdcGetValue(ADC_ARRAY_AI+j) > 1500) {
                return 1;
            }
        }
    }

    return 0;
}