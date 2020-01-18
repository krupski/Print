//////////////////////////////////////////////////////////////////////////////////////
//
//  Print.cpp - Base class that provides print() and println()
//  Copyright (c) 2008 David A. Mellis. All right reserved.
//  Copyright (c) 2019 Roger A. Krupski. All right reserved.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
//  Modified 23 November 2006 by David A. Mellis
//  Modified 03 October 2019 by Roger A. Krupski
//   * can print 64 bit numbers (uses no extra ram)
//   * improved and extended floating point print code
//   * printing a string with "\n" in it automatically adds the "\r"
//   * adds print_P and println_P (print strings from PROGMEM a.k.a. Flash)
//   * adds print_E and println_E (print strings from EEMEM a.k.a. EEProm)
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "WString.h"
#include "Printable.h"

#define BIN  2
#define OCT  8
#define DEC 10
#define HEX 16

class Print {
	public:
		Print () : write_error (0) { ; }
		int getWriteError (void) { return write_error; }
		void clearWriteError (void) { setWriteError (0); }

		virtual size_t write (uint8_t) = 0;
		virtual size_t write (const uint8_t *, size_t);

		int availableForWrite (void) { return 0; }
		void flush (void) { /* Empty implementation for backward compatibility */ }
		int available (void) { return 0; }
		int read (void) { return 0; }

		size_t print (uint8_t,     uint8_t=DEC, uint8_t=0);
		size_t print (uint16_t,    uint8_t=DEC, uint8_t=0);
		size_t print (uint32_t,    uint8_t=DEC, uint8_t=0);
		size_t print (uint64_t,    uint8_t=DEC, uint8_t=0);

		size_t println (uint8_t,   uint8_t=DEC, uint8_t=0);
		size_t println (uint16_t,  uint8_t=DEC, uint8_t=0);
		size_t println (uint32_t,  uint8_t=DEC, uint8_t=0);
		size_t println (uint64_t,  uint8_t=DEC, uint8_t=0);

		size_t print (int8_t,      uint8_t=DEC, uint8_t=0);
		size_t print (int16_t,     uint8_t=DEC, uint8_t=0);
		size_t print (int32_t,     uint8_t=DEC, uint8_t=0);
		size_t print (int64_t,     uint8_t=DEC, uint8_t=0);

		size_t println (int8_t,    uint8_t=DEC, uint8_t=0);
		size_t println (int16_t,   uint8_t=DEC, uint8_t=0);
		size_t println (int32_t,   uint8_t=DEC, uint8_t=0);
		size_t println (int64_t,   uint8_t=DEC, uint8_t=0);

		size_t print (float,         uint8_t=2, uint8_t=0);
		size_t print (double,        uint8_t=2, uint8_t=0);
		size_t print (long double,   uint8_t=2, uint8_t=0);

		size_t println (float,       uint8_t=2, uint8_t=0);
		size_t println (double,      uint8_t=2, uint8_t=0);
		size_t println (long double, uint8_t=2, uint8_t=0);

		size_t print (char);
		size_t print   (const void *);
		size_t print_P (const void *);
		size_t print_E (const void *);
		size_t print (const String &);
		size_t print (const __FlashStringHelper *);
		size_t print (const Printable &);

		size_t println (char);
		size_t println   (const void *);
		size_t println_P (const void *);
		size_t println_E (const void *);
		size_t println (const String &);
		size_t println (const __FlashStringHelper *);
		size_t println (const Printable &);

		size_t println (void);

	private:
		int write_error;
		template <class T> size_t printInteger (T, uint8_t, uint8_t);
		template <class T> size_t printDouble (T, uint8_t, uint8_t);
		uint64_t intPower (uint8_t, uint8_t);

	protected:
		void setWriteError (int err=1) { write_error = err; }
};

#endif // #ifndef PRINT_H

// end of Print.h
