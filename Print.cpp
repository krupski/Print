//////////////////////////////////////////////////////////////////////////////////////
//
//  Print.cpp - Base class that provides print() and println()
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#if ARDUINO < 100
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

#include "Print.h"

// Public Methods
// default implementation: may be overridden
size_t Print::write (const uint8_t *str, size_t siz)
{
	size_t n = 0;

	while (siz--) {
		write (str[n++]);
	}

	return n;
}

/////////////////////// unsigned, print() ///////////////////////
size_t Print::print (uint8_t value, uint8_t base)
{
	return printNumber (value, base, _unsigned);
}

size_t Print::print (uint16_t value, uint8_t base)
{
	return printNumber (value, base, _unsigned);
}

size_t Print::print (uint32_t value, uint8_t base)
{
	return printNumber (value, base, _unsigned);
}

size_t Print::print (uint64_t value, uint8_t base)
{
	return printNumber (value, base, _unsigned);
}

/////////////////////// unsigned, println() ///////////////////////
size_t Print::println (uint8_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

size_t Print::println (uint16_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

size_t Print::println (uint32_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

size_t Print::println (uint64_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

/////////////////////// signed, print() ///////////////////////
size_t Print::print (const char *str)
{
	size_t n = 0;
	char c;

	while ((c = str[n++])) {
		if (c == '\n') {
			write ('\r');
		}

		write (c);
	}

	return n;
}

size_t Print::print (char c)
{
	return write (c);
}

size_t Print::print (int8_t value, uint8_t base)
{
	return printNumber (value, base, _signed);
}

size_t Print::print (int16_t value, uint8_t base)
{
	return printNumber (value, base, _signed);
}

size_t Print::print (int32_t value, uint8_t base)
{
	return printNumber (value, base, _signed);
}

size_t Print::print (int64_t value, uint8_t base)
{
	return printNumber (value, base, _signed);
}

/////////////////////// signed, println() ///////////////////////
size_t Print::println (const char *str)
{
	size_t n = print (str);
	return (n + println());
}

size_t Print::println (char c)
{
	size_t n = write (c);
	return (n + println());
}

size_t Print::println (int8_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

size_t Print::println (int16_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

size_t Print::println (int32_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

size_t Print::println (int64_t value, uint8_t base)
{
	size_t n = print (value, base);
	return (n + println());
}

//////////// print() and println(), floating point ////////////
size_t Print::print (double value, uint8_t digits)
{
	return printFloat (value, digits);
}

size_t Print::println (double value, uint8_t digits)
{
	size_t n = print (value, digits);
	return (n + println());
}

//////////// signed, print() and println(), PROGMEM strings ////////////
size_t Print::print (const __FlashStringHelper *ifsh)
{
	PGM_P p = reinterpret_cast<PGM_P> (ifsh);
	size_t n = 0;
	unsigned char c;

	while ((c = PGM_R (p + n++))) {
		write (c);
	}

	return n;
}

size_t Print::println (const __FlashStringHelper *ifsh)
{
	size_t n = print (ifsh);
	return (n + println());
}

// print_P, signed
size_t Print::print_P (const char *str)
{
	size_t n = 0;
	char c;

	while (c = PGM_R (str + n++)) {
		write (c);
	}

	return n;
}

// println_P, signed
size_t Print::println_P (const char *str)
{
	size_t n = print_P (str);
	return (n + println());
}

// print_E, EEMEM (eeprom) strings ////
size_t Print::print_E (const char *str)
{
	size_t n = 0;
	char c;

	while (c = eeprom_read_byte ((const uint8_t *) str + n++)) {
		write (c);
	}

	return n;
}

size_t Print::println_E (const char *str)
{
	size_t n = print_E (str);
	return (n + println());
}

//////////// print() and println(), String() class ////////////
size_t Print::print (const String &s)
{
	return write (s.c_str(), s.length());
}

size_t Print::println (const String &s)
{
	size_t n = write (s.c_str(), s.length());
	return (n + println());
}

//////////// print() and println(), Printable ////////////
size_t Print::print (const Printable &s)
{
	return s.printTo (*this);
}

size_t Print::println (const Printable &s)
{
	size_t n = s.printTo (*this);
	return (n + println());
}

//////////// we all need println()! ////////////
size_t Print::println (void)
{
	return print ("\n");
}

// Private Methods /////////////////////////////////////////////////////////////
// if "sign" == true then input is a signed value, else it's unsigned
size_t Print::printNumber (int64_t value, uint8_t base, uint8_t sign)
{
	size_t n = 0;
	uint8_t idx;
	uint8_t pow;
	int64_t val;
	static const uint8_t chars[] PROGMEM = "0123456789ABCDEF-";

	if (!value) {
		return write (PGM_R (chars + 0));
	}

	if (base == DEC && value < 0 && sign) {
		n += write (PGM_R (chars + 16));
		value = -value;
	}

	pow = 0;
	val = value;

	// if base < 2 then default to decimal (prevent crash if base == 0)
	// if base > 16 then default to hex
	base = base < BIN ? DEC : base > HEX ? HEX : base;

	while (val) {
		val /= base;
		pow++;
	}

	while (pow--) {
		idx = value / intPower (base, pow);
		value -= idx * intPower (base, pow);
		n += write (PGM_R (chars + idx));
	};

	return n;
}

// this is a really crappy way to print floating point numbers....
size_t Print::printFloat (double value, uint8_t digits)
{
	size_t n = 0;

	if (isnan (value)) {
		return write ("nan");
	}

	if (isinf (value)) {
		return write ("inf");
	}

	if ((value < -4294967167.0) || (value > 4294967167.0)) {
		return write ("ovf");
	}

	// Handle negative numbers
	if (value < 0.0) {
		n += write ('-');
		value = -value;
	}

	// Round correctly so that print (1.999, 2) prints as "2.00"
	double rounding = 0.5;
	double remainder;

	uint8_t i;
	uint64_t int_part;

	int toPrint;

	for (i = 0; i < digits; i++) {
		rounding /= 10.0;
	}

	value += rounding;

	// Extract the integer part of the number and print it
	int_part = (uint64_t) value;
	remainder = (value - (double) int_part);

	n += print (int_part);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0) {
		n += write ('.');
	}

	// Extract digits from the remainder one at a time
	while (digits-- > 0) {
		remainder *= 10.0;
		toPrint = int (remainder);
		n += print (toPrint);
		remainder -= toPrint;
	}

	return n;
}

// performs base to the exp power
uint64_t Print::intPower (uint8_t base, uint8_t exp)
{
	uint64_t result = 1;

	while (exp--) {
		result *= base;
	}

	return result;
}

///////// end of print.cpp ////////
