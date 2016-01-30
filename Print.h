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
//  Modified 30 January 2016 by Roger A. Krupski <rakrupski@verizon.net>
//   * can print 64 bit numbers
//   * does not use any buffer to print
//   * adds print_P and println_P (print strings from PROGMEM a.k.a. Flash)
//   * adds print_E and println_E (print strings from EEMEM a.k.a. EEProm)
//   * printing a string with "\n" in it automatically adds the "\r"
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _PRINT_H
#define _PRINT_H

#define BIN  2
#define OCT  8
#define DEC 10
#define HEX 16

#define _unsigned 0
#define _signed 1

#include <inttypes.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "WString.h"
#include "Printable.h"

#define ARDUINO_CORE_PRINTABLE_SUPPORT

class Print;

class _Printable {
	public:
		virtual void print (Print &stream) const = 0;
};

class Print {
	public:
		Print (void) : write_error (0) {}
		int getWriteError (void) {
			return write_error;
		}
		void clearWriteError (void) {
			setWriteError (0);
		}
		virtual size_t write (uint8_t) = 0;
		size_t write (const char *str) {
			if (str == NULL) {
				return 0;
			}
			return write ((const uint8_t *) str, strlen (str));
		}
		virtual size_t write (const uint8_t *buffer, size_t size);
		size_t write (const char *buffer, size_t size) {
			return write ((const uint8_t *)buffer, size);
		}
		void print (const _Printable &obj) {
			obj.print (*this);
		}
		void println (const _Printable &obj) {
			obj.print (*this); println();
		}
		// unsigned
		size_t print (uint8_t, uint8_t = 10);
		size_t print (uint16_t, uint8_t = 10);
		size_t print (uint32_t, uint8_t = 10);
		size_t print (uint64_t, uint8_t = 10);
		size_t println (uint8_t, uint8_t = 10);
		size_t println (uint16_t, uint8_t = 10);
		size_t println (uint32_t, uint8_t = 10);
		size_t println (uint64_t, uint8_t = 10);
		// unsigned, EEPROM
		size_t print_E (const uint8_t *);
		size_t println_E (const uint8_t *);
		// signed
		size_t print (const char *);
		size_t print (char);
		size_t print (int8_t, uint8_t = 10);
		size_t print (int16_t, uint8_t = 10);
		size_t print (int32_t, uint8_t = 10);
		size_t print (int64_t, uint8_t = 10);
		size_t println (const char *);
		size_t println (char);
		size_t println (int8_t, uint8_t = 10);
		size_t println (int16_t, uint8_t = 10);
		size_t println (int32_t, uint8_t = 10);
		size_t println (int64_t, uint8_t = 10);
		// floating point
		size_t print (double, uint8_t = 2);
		size_t println (double, uint8_t = 2);
		// PROGMEM
		size_t print (const __FlashStringHelper *);
		size_t println (const __FlashStringHelper *);
		size_t print_P (const char *);
		size_t println_P (const char *);
		// String
		size_t print (const String &);
		size_t println (const String &);
		// Printable
		size_t print (const Printable &);
		size_t println (const Printable &);
		// Everyone needs println()
		size_t println (void);
	private:
		int write_error;
		size_t printNumber (int64_t, uint8_t, uint8_t);
		size_t printFloat (double, uint8_t);
		uint64_t intPower (uint8_t, uint8_t);
#ifdef pgm_read_byte_far
#define PGM_R pgm_read_byte_far
#else
#define PGM_R pgm_read_byte_near
#endif
	protected:
		void setWriteError (int err = 1) {
			write_error = err;
		}
};
#endif
