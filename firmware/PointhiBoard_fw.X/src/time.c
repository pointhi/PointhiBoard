/**
 * @file time.c
 *
 * @author thomas
 *
 * @date 29. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#include "time.h"
#include <pic18.h>

#define TIME_TIMESTAMP_RESET    10000
#define TIME_TIMER_TICKS_S      50
#define TIME_TIMER_TICK         1000 / TIME_TIMER_TICKS_S

unsigned int timeTimestampMs = 0;

void TimeInterrupt() {
    timeTimestampMs += TIME_TIMER_TICK;
    if(timeTimestampMs >= TIME_TIMESTAMP_RESET) {
        timeTimestampMs -= TIME_TIMESTAMP_RESET;
    }
}

unsigned int TimeGetTimestamp() {
    return timeTimestampMs;
}

unsigned int TimeGetDifference(unsigned int _lower_timestamp, unsigned int _higher_timestamp) {
    if(_lower_timestamp <= _higher_timestamp) {
        return _higher_timestamp - _lower_timestamp;
    } else {
        return TIME_TIMESTAMP_RESET-_higher_timestamp + _lower_timestamp;
    }
}

void TimeWaitMs(unsigned int _delay) {
    unsigned int currentTimestampMs = TimeGetTimestamp();
    while(TimeGetDifference(currentTimestampMs,TimeGetTimestamp()) < _delay && _delay < TIME_TIMESTAMP_RESET-TIME_TIMER_TICK);
}