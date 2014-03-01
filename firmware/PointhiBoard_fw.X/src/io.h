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

void IoSetLedInfo(unsigned char _ledMacro);
void IoSetLedStat(unsigned char _ledMacro);

void IoGotoNextMacroBit();
void IoUpdateLedOutput();

void IoSetFet5v(unsigned char _value);
void IoSetFetVcc(unsigned char _value);

#endif	/* IO_H */

