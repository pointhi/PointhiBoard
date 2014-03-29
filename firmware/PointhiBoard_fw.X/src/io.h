/**
 * @file io.h
 *
 * @author thomas
 *
 * @date 1. March 2014
 * @copyright GNU General Public License (GPL) 3.0
 */

#ifndef IO_H
#define	IO_H

inline void IoSetLedInfo(const unsigned char _ledMacro);
inline void IoSetLedStat(const unsigned char _ledMacro);

void IoGotoNextMacroBit();
void IoUpdateLedOutput();

void IoSetFet5v(const unsigned char _value);
void IoSetFetVcc(const unsigned char _value);

#endif	/* IO_H */

