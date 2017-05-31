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
//  Modified 15 April 2016 by Roger A. Krupski <rakrupski@verizon.net>
//    * can print 64 bit numbers
//    * does not use any buffer to print
//    * adds print_P and println_P (print strings from PROGMEM a.k.a. Flash)
//    * adds print_E and println_E (print strings from EEMEM a.k.a. EEProm)
//    * printing a string with "\n" in it automatically adds the "\r"
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
		write (*(str + n++));
	}

	return n;
}

/////////////////////// unsigned, print() ///////////////////////
size_t Print::print (uint8_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

size_t Print::print (uint16_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

size_t Print::print (uint32_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

size_t Print::print (uint64_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

/////////////////////// unsigned, println() ///////////////////////
size_t Print::println (uint8_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

size_t Print::println (uint16_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

size_t Print::println (uint32_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

size_t Print::println (uint64_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

/////////////////////// signed, print() ///////////////////////
size_t Print::print (const void *str)
{
	size_t n = 0;
	char *ptr;
	char c;

	ptr = (char *) str;

	while ((c = *ptr++)) {
		n += print ((char) c);
	}

	return n;
}

size_t Print::print (char c)
{
	size_t n = 0;

	if (c == '\n') {
		n += write ((char) '\r'); // add CR to LF
	}

	n += write ((char) c);

	return n;
}

size_t Print::print (int8_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

size_t Print::print (int16_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

size_t Print::print (int32_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

size_t Print::print (int64_t value, int8_t base, int8_t chars)
{
	return printInteger (value, base, chars);
}

/////////////////////// signed, println() ///////////////////////
size_t Print::println (const void *str)
{
	size_t n = print ((const char *) str);
	return (n + println());
}

size_t Print::println (char c)
{
	size_t n = print ((char) c);
	return (n + println());
}

size_t Print::println (int8_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

size_t Print::println (int16_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

size_t Print::println (int32_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

size_t Print::println (int64_t value, int8_t base, int8_t chars)
{
	size_t n = print (value, base, chars);
	return (n + println());
}

//////////// print() and println(), floating point ////////////
size_t Print::print (float value, int8_t chars, int8_t prec)
{
	return printDouble (value, chars, prec);
}

size_t Print::println (float value, int8_t chars, int8_t prec)
{
	size_t n = print (value, chars, prec);
	return (n + println ());
}

size_t Print::print (double value, int8_t chars, int8_t prec)
{
	return printDouble (value, chars, prec);
}

size_t Print::println (double value, int8_t chars, int8_t prec)
{
	size_t n = print (value, chars, prec);
	return (n + println());
}

size_t Print::print (long double value, int8_t chars, int8_t prec)
{
	return printDouble (value, chars, prec);
}

size_t Print::println (long double value, int8_t chars, int8_t prec)
{
	size_t n = print (value, chars, prec);
	return (n + println());
}

//////////// print() and println(), FLASH strings ////////////
size_t Print::print (const __FlashStringHelper *ifsh)
{
	PGM_P ptr = reinterpret_cast <PGM_P> (ifsh);
	size_t n = 0;
	char c;

	while ((c = pgm_read_byte (ptr++))) {
		n += print ((char) c);
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
	char *ptr;

	ptr = (char *) str;

	while ((c = pgm_read_byte (ptr++))) {
		n += print ((char) c);
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
	uint8_t *ptr;

	ptr = (uint8_t *) str;

	while ((c = eeprom_read_byte (ptr++))) {
		n += print ((char) c);
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
		n += print ((char) *ptr++);
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
	return print ((char) '\n');
}

// Private Methods /////////////////////////////////////////////////////////////
template <class T> size_t Print::printInteger (T value, int8_t base, int8_t chars)
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

	if (chars > 16) {
		chars = 16; // no more than 16 character places
	}

	// print at least req'd number of chars, or more.
	chars = pow < chars ? chars : pow;

	while (chars--) { // print each character

		idx = ((value / intPower (base, chars)) % base); // get a digit
		value -= (idx * intPower (base, chars)); // subtract from what's left

		if (idx > 9) {
			idx += 7; // print hex A-F
		}

		if (chars < pow) { // if it's part of the actual number
			n += print ((char)(idx + '0'));

		} else { // else it's a padding character
			n += print ((char) pad);
		}
	}

	return n;
}

size_t Print::printDouble (double value, int chars, int prec)
{
	size_t n = 0;
	int frac;
	char *buf;
	int64_t val;

	if ((chars == -1) && (prec == -1)) {
		prec = 2; // backwards compatible
		chars = 0;
	}

	if ((chars != -1) && (prec == -1)) {
		prec = chars; // if precision only is specified
		chars = 0;
	}

	frac = (prec + 1); // fractional part plus decimal point (borrow n)

	val = value;

	while (val) { // find out how many digits we are gonna print
		frac++; // count digit
		val /= 10; // next digit
	}

	frac = (chars > frac) ? chars : frac; // if we need more buffer....

	frac += 2; // account for possible minus sign and EOL

	// allocate buffer for dtostrf()
	buf = (char *) malloc (frac * sizeof (char));

	if (!buf) { // if malloc fails, say so
		print_P (F("malloc?"));
		n = 0;
		return n;
	}

	dtostrf (value, chars, prec, buf); // convert to buffer
	n = print (buf); // print it
	free (buf); // free allocated buffer

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

// dummies for stdio compatability
int Print::available (void)
{
	return 0;
}

int Print::read (void)
{
	return 0;
}

int Print::peek (void)
{
	return 0;
}

void Print::flush (void)
{
	// void so nothing
}

///////// end of print.cpp ////////
