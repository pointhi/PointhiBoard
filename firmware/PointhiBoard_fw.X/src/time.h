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

inline void TimeInterrupt();

inline unsigned int TimeGetTimestamp();
unsigned int TimeGetDifference(const unsigned int _lower_timestamp, const unsigned int _higher_timestamp);

void TimeWaitMs(const unsigned int _delay);

#endif	/* TIME_H */

