//////////////////////////////////////////////////////////////////////////////////////
//
//  Print.h - Base class that provides print() and println()
//  Copyright (c) 2008 David A. Mellis. All right reserved.
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
//  Modified 23 November 2006 by David A. Mellis
//  Modified 15 April 2016 by Roger A. Krupski <rakrupski@verizon.net>
//    * can print 64 bit numbers
//    * does not use any buffer to print
//    * adds print_P and println_P (print strings from PROGMEM a.k.a. Flash)
//    * adds print_E and println_E (print strings from EEMEM a.k.a. EEProm)
//    * printing a string with "\n" in it automatically adds the "\r"
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

#define ARDUINO_CORE_PRINTABLE_SUPPORT

class Print;

class _Printable {
	public:
		virtual void print (Print &stream) const = 0;
};

class Print {
	public:
		Print() : write_error (0) {}
		int getWriteError() { return write_error; }
		void clearWriteError() { setWriteError (0); }
		void setWriteError (int err = 1) {
			write_error = err;
		}
		// dummies for stdio compatibility
		virtual int available (void);
		virtual int read (void);
		virtual int peek (void);
		virtual void flush (void);
		operator bool (void) {
			return true;
		}

		virtual size_t write (uint8_t);
		size_t write (const char *str) {
			if (str == NULL) {
				return 0;
			}
			return write ((const uint8_t *) str, strlen (str));
		}

		virtual size_t write (const uint8_t *, size_t);

		size_t write (const char *buffer, size_t siz) {
			return write ((const uint8_t *) buffer, siz);
		}

		size_t print (uint8_t, int8_t=DEC, int8_t=0);
		size_t print (uint16_t, int8_t=DEC, int8_t=0);
		size_t print (uint32_t, int8_t=DEC, int8_t=0);
		size_t print (uint64_t, int8_t=DEC, int8_t=0);

		size_t println (uint8_t, int8_t=DEC, int8_t=0);
		size_t println (uint16_t, int8_t=DEC, int8_t=0);
		size_t println (uint32_t, int8_t=DEC, int8_t=0);
		size_t println (uint64_t, int8_t=DEC, int8_t=0);

		size_t print (const void *);
		size_t print (char);
		size_t print (int8_t, int8_t=DEC, int8_t=0);
		size_t print (int16_t, int8_t=DEC, int8_t=0);
		size_t print (int32_t, int8_t=DEC, int8_t=0);
		size_t print (int64_t, int8_t=DEC, int8_t=0);

		size_t println (const void *);
		size_t println (char);
		size_t println (int8_t, int8_t=DEC, int8_t=0);
		size_t println (int16_t, int8_t=DEC, int8_t=0);
		size_t println (int32_t, int8_t=DEC, int8_t=0);
		size_t println (int64_t, int8_t=DEC, int8_t=0);

		size_t print (float, int8_t=-1, int8_t=-1);
		size_t println (float, int8_t=-1, int8_t=-1);

		size_t print (double, int8_t=-1, int8_t=-1);
		size_t println (double, int8_t=-1, int8_t=-1);

		size_t print (long double, int8_t=-1, int8_t=-1);
		size_t println (long double, int8_t=-1, int8_t=-1);

		size_t print (const __FlashStringHelper *);
		size_t println (const __FlashStringHelper *);

		size_t print_P (const void *);
		size_t println_P (const void *);

		size_t print_E (const void *);
		size_t println_E (const void *);

		size_t print (const String &);
		size_t println (const String &);

		size_t print (const Printable &);
		size_t println (const Printable &);

		size_t println (void);

	private:
		int write_error;
		template <class T> size_t printInteger (T, int8_t, int8_t);
		size_t printDouble (double, int, int);
		uint64_t intPower (uint8_t, uint8_t);
};

#endif

// end of Print.h
