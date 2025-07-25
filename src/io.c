#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "io.h"
#include "utils.h"


#define INV_CURR 0


/*
 * Shared Variables
 */

// Shared private buffer used for IO operations as needed
static char io_buffer[MAX_BUFFER_SIZE];


/*
 * Static Functions (marked with s_ prefix)
 */

// Prototypes used by curr_to_str and str_to_curr
static Currency s_get_units(char**);
static Currency s_get_cents(char**);
static unsigned s_get_multiplier(char**);

// Convert an amount of currency into its str representation, then save it to the IO buffer
static char *s_currency_to_str(Currency amount) {
	uint64 unit_count = (uint64) (amount / 100);
	uint8 cent_count = (uint8) (amount % 100);

	// Place unit portion's str representation in buffer, record the len of the output
	int unit_len = snprintf(io_buffer, MAX_BUFFER_SIZE, "%s%'d", CURRENCY_SYM, unit_count);

	// If the buffer isn't full
	if (unit_len+1 < MAX_BUFFER_SIZE) {
		// Append the cent str representation to the buffer
		snprintf(io_buffer+unit_len, MAX_BUFFER_SIZE-unit_len, ".%02d", cent_count);
	}
	
	// Return a reference to IO buffer
	return io_buffer;
}

// Convert the str in the IO buffer into the amount of currency it represents, if possible
static Currency s_str_to_currency() {
	char *s = io_buffer, *sym_s = CURRENCY_SYM;
	Currency out = 0;
	// Skip whitespace
	while (isspace(*s)) 
		s++;
	// Skip currency string
	while (*s == *sym_s) {
		sym_s++;
		s++;
	}
	if (!isdigit(*s))  // Inputs containing excess non-digits are invalid
		return INV_CURR;
	out += s_get_units(&s);
	out += s_get_cents(&s);
	out *= s_get_multiplier(&s);
	if (*s != '\0')   // Inputs of excess length are invalid
		return INV_CURR;
	return out;
}

static Currency s_get_units(char **pstr) {
	Currency out = 0;
	int len;
	if (sscanf(*pstr, "%lu%n", &out, &len) > 0) {
		out *= 100;
		*pstr += len;
	}
	return out;
}

static Currency s_get_cents(char **pstr) {
	Currency out = 0;
	unsigned base = 10;
	if (**pstr == '.') {
		(*pstr)++;
		while (isdigit(**pstr)) {
			out += base * (*(*pstr)++ - '0');
			base /= 10;
		}
	}
	return out;
}

static unsigned s_get_multiplier(char** pstr) {
	if (tolower(**pstr) != 'x')
		return 1;  // No multiplier given 
	(*pstr)++;
	unsigned out = 0;
	while (isdigit(**pstr)) {
		out *= 10;
		out += *(*pstr)++ - '0';
	}
	return out;
}


/*
 * Public Functions
 */

/**
Insert the string representation of an amount of currency into a format string,
	then place the result into a char buffer
@param out
	A pointer to the buffer where the final output is stored
@param len
	The length of the output buffer
@param format
	A format string, as used in printf. Must include at least one instance of
	%s, which will be replaced with the currency's str representation
@param amount
	The amount of currency to be represented as a str
@return 
	A pointer to the output buffer
*/
char *sprint_currency(char *out, size_t len, char *format, Currency amount) {
	char *currency_str = s_currency_to_str(amount);
	snprintf(out, len, format, currency_str);
	return out;
}

/**
Print the string representation of an amount of currency to a file stream
@param file
	A pointer to the file stream to which the output will be printed
@param format
	A format string, as used in printf. Must include at least one instance of
	%s, which will be replaced with the currency's str representation
@param amount
	The amount of currency to be represented as a str
@return
	A pointer to the output file stream
*/		
FILE *fprint_currency(FILE *file, char *format, Currency amount) {
	char *currency_str = s_currency_to_str(amount);
	fprintf(file, format, currency_str);
	return file;
}

/**
Print the string representation of an amount of currency to stdout
@param format
	A format string, as used in printf. Must include at least one instance of
	%s, which will be replaced with the currency's str representation
@param amount
	The amount of currency to be represented as a str
*/		
void print_currency(char *format, Currency amount) {
	fprint_currency(stdout, format, amount);
}

/**
Scan a string for the string representation of a currency value,
	then return that value
@param in
	The string to be scanned
@return
	The currency value represented in the string
*/
Currency sscan_currency(char *in) {
	// Copy the input str to the IO buffer
	strncpy(io_buffer, in, MAX_BUFFER_SIZE-1);
	return s_str_to_currency();
}

/**
Scan a file stream for the string representation of a currency value,
	then return that value
@param in
	The file stream to be scanned
@return
	The currency value represented in the file stream
*/
Currency fscan_currency(FILE *in) {
	// Generate a format specifying the maximum length of the IO buffer
	char format[MIN_BUFFER_SIZE];
	snprintf(format, MIN_BUFFER_SIZE, "%%%ds", MAX_BUFFER_SIZE-1);
	// Use format to read from the input stream to the IO buffer
	fscanf(in, format, &io_buffer);
	return s_str_to_currency();
}

