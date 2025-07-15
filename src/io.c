#include <stdio.h>
#include <string.h>

#include "io.h"
#include "utils.h"


/*
 * Shared Variables
 */

// Shared private buffer used for IO operations as needed
static char io_buffer[MAX_BUFFER_SIZE];


/*
 * Static Functions (marked with s_ prefix)
 */

// Convert an amount of currency into its str representation, then save it to the IO buffer
static char *s_currency_to_str(Currency amount) {
	uint64 unit_count = (uint64) (amount / 100);
	uint8 cent_count = (uint8) (amount % 100);

	// Place unit portion's str representation in buffer, record the len of the output
	int unit_len = snprintf(io_buffer, MAX_BUFFER_SIZE, "%s%'d", CURRENCY_SYM, unit_count);

	// If there's a cent portion and buffer isn't full
	if (cent_count > 0 && unit_len+1 < MAX_BUFFER_SIZE) {
		// Append the cent str representation to the buffer
		snprintf(io_buffer+unit_len, MAX_BUFFER_SIZE-unit_len, ".%02d", cent_count);
	}
	
	// Return a reference to IO buffer
	return io_buffer;
}

static Currency s_str_to_currency() {
	return (Currency) 0;
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
	A format string, as used in printf
@param amount
	The amount of currency to be represented
@return 
	A pointer to the output buffer
*/
char *sprint_currency(char *out, size_t len, char *format, Currency amount) {
	char *currency_str = s_currency_to_str(amount);
	snprintf(out, len, format, currency_str);
	return out;
}

