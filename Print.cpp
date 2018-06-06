//////////////////////////////////////////////////////////////////////////////////////
//
//  Print.cpp - Base class that provides print() and println()
//  Copyright (c) 2008 David A. Mellis. All right reserved.
//  Copyright (c) 2017 Roger A. Krupski. All right reserved.
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
//  Modified 18 December 2017 by Roger A. Krupski <rakrupski@verizon.net>
//   * can print 64 bit numbers
//   * adds print_P and println_P (print strings from PROGMEM a.k.a. Flash)
//   * adds print_E and println_E (print strings from EEMEM a.k.a. EEProm)
//   * printing a string with "\n" in it automatically adds the "\r"
//
//////////////////////////////////////////////////////////////////////////////////////

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
		write (* (str + n));
		n++;
	}

	return n;
}

/////////////////////// unsigned, print() ///////////////////////
size_t Print::print (uint8_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

size_t Print::print (uint16_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

size_t Print::print (uint32_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

size_t Print::print (uint64_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

/////////////////////// unsigned, println() ///////////////////////
size_t Print::println (uint8_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

size_t Print::println (uint16_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

size_t Print::println (uint32_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

size_t Print::println (uint64_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

/////////////////////// signed, print() ///////////////////////
size_t Print::print (const void *str)
{
	size_t n = 0;
	char c;

	while ((c = * ((const char *)(str + n)))) {
		print ((char) c);
		n++;
	}

	return n;
}

size_t Print::print (char c)
{
	size_t n = 0;

	if (c == '\n') {
		n += write ((uint8_t) '\r'); // add CR to LF
	}

	n += write ((uint8_t) c);
	return n;
}

size_t Print::print (int8_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

size_t Print::print (int16_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

size_t Print::print (int32_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

size_t Print::print (int64_t value, uint8_t base, uint8_t digits)
{
	return printInteger (value, base, digits);
}

/////////////////////// signed, println() ///////////////////////
size_t Print::println (const void *str)
{
	size_t n = print (str);
	return (n + println());
}

size_t Print::println (char c)
{
	size_t n = print ((char) c);
	return (n + println());
}

size_t Print::println (int8_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

size_t Print::println (int16_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

size_t Print::println (int32_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

size_t Print::println (int64_t value, uint8_t base, uint8_t digits)
{
	size_t n = print (value, base, digits);
	return (n + println());
}

//////////// print() and println(), floating point ////////////
size_t Print::print (float value, uint8_t prec, uint8_t digits)
{
	return printDouble (value, prec, digits);
}

size_t Print::println (float value, uint8_t prec, uint8_t digits)
{
	size_t n = print (value, prec, digits);
	return (n + println());
}

size_t Print::print (double value, uint8_t prec, uint8_t digits)
{
	return printDouble (value, prec, digits);
}

size_t Print::println (double value, uint8_t prec, uint8_t digits)
{
	size_t n = print (value, prec, digits);
	return (n + println());
}

size_t Print::print (long double value, uint8_t prec, uint8_t digits)
{
	return printDouble (value, prec, digits);
}

size_t Print::println (long double value, uint8_t prec, uint8_t digits)
{
	size_t n = print (value, prec, digits);
	return (n + println());
}

//////////// print() and println(), FLASH strings ////////////
size_t Print::print (const __FlashStringHelper *ifsh)
{
	PGM_P ptr = reinterpret_cast <PGM_P> (ifsh);
	size_t n = 0;
	char c;

#if defined (pgm_read_byte_far)
	while ((c = pgm_read_byte_far (ptr + n))) {
#else
	while ((c = pgm_read_byte_near (ptr + n))) {
#endif
		print ((char) c);
		n++;
	}

	return n;
}

size_t Print::println (const __FlashStringHelper *ifsh)
{
	size_t n = print (ifsh);
	return (n + println());
}

size_t Print::print_P (const void *str)
{
	size_t n = 0;
	char c;

#if defined (pgm_read_byte_far)
	while ((c = pgm_read_byte_far (str + n))) {
#else
	while ((c = pgm_read_byte_near (str + n))) {
#endif
		print ((char) c);
		n++;
	}

	return n;
}

size_t Print::println_P (const void *str)
{
	size_t n = print_P (str);
	return (n + println());
}

//////////// print() and println(), EEPROM strings ////////////
size_t Print::print_E (const void *str)
{
	size_t n = 0;
	char c;

	while ((c = eeprom_read_byte ((const uint8_t *)(str + n)))) {
		print ((char) c);
		n++;
	}

	return n;
}

size_t Print::println_E (const void *str)
{
	size_t n = print_E (str);
	return (n + println());
}

//////////// print() and println(), String() class ////////////
size_t Print::print (const String &s)
{
	size_t n = 0;
	size_t len = s.length();
	char *ptr = (char *) s.c_str();

	while (len--) {
		n += print ((char) * ptr++);
	}

	return n;
}

size_t Print::println (const String &s)
{
	size_t n = print (s.c_str());
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
	return write ("\r\n");
}

// Private Methods /////////////////////////////////////////////////////////////
template <class T> size_t Print::printInteger (T value, uint8_t base, uint8_t digits)
{
	size_t n = 0;
	int8_t idx;
	int8_t pow;
	uint8_t pad;

	T val;

	val = -1; // prepare for signed/unsigned test

	if (val < 0) { // if unsigned it's never less than 01
		if ((value < 0) && (base == DEC)) { // less than 0 means it's signed so...
			value = -value; // ... if actual value is negative invert it (decimal only)
			n += print ((char) '-'); // minus sign
		}
	}

	// if base < 2 then default to decimal (prevent crash if base == 0)
	// if base > 16 then default to hex
	base = base < BIN ? DEC : base > HEX ? HEX : base;

	if (base == DEC) { // pad decimal with spaces...
		pad = ' '; // ascii space

	} else { // ...pad all else with zero
		pad = '0'; // ascii zero
	}

	pow = 1; // initialize power value
	val = value; // make a scrap copy of "value"

	while (val /= base) {
		pow++; // how many digits in "value" with a base of "base"
	}

	if (digits > 16) {
		digits = 16; // no more than 16 character places
	}

	// print at least req'd number of chars, or more.
	digits = pow < digits ? digits : pow;

	while (digits--) { // print each character
		idx = ((value / intPower (base, digits)) % base); // get a digit
		value -= (idx * intPower (base, digits)); // subtract from what's left

		if (idx > 9) {
			idx += 7; // print hex A-F
		}

		if (digits < pow) { // if it's part of the actual number
			n += print ((char)(idx + '0'));

		} else { // else it's a padding character
			n += print ((char) pad);
		}
	}

	return n;
}

size_t Print::printDouble (long double value, uint8_t prec, uint8_t digits)
{
	char buf [32];
	dtostrf (value, digits, prec, buf); // convert to buffer
	return print (buf); // print it
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
