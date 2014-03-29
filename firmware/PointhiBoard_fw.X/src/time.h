/**
 * @file time.h
 *
 * @author thomas
 *
 * @date 29. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#ifndef TIME_H
#define	TIME_H

void TimeInterrupt();

unsigned int TimeGetTimestamp();
unsigned int TimeGetDifference(unsigned int _lower_timestamp, unsigned int _higher_timestamp);

void TimeWaitMs(unsigned int _delay);

#endif	/* TIME_H */

