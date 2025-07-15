#include <stdio.h>
#include <string.h>

#include "io.h"
#include "utils.h"


// Shared private buffer used for IO operations as needed
static char *io_buffer[MAX_BUFFER_SIZE];


char *currency_to_str(char *buffer, size_t buffer_size, Currency amount) {
	uint64 unit_count = (uint64) (amount / 100);
	uint8 cent_count = (uint8) (amount % 100);

	// Place unit str representation in buffer
	snprintf(buffer, buffer_size, "%s%'d", CURRENCY_SYM, unit_count);
	int unit_len = strlen(buffer);

	// If there's a cent portion and buffer isn't full
	if (cent_count > 0 && unit_len+1 < buffer_size) {
		// Append the cent str representation to the buffer
		snprintf(buffer+unit_len, buffer_size-unit_len, ".%02d", cent_count);
	}

	// Pass pointer to the buffer arg back to the caller
	return buffer;
}

Currency str_to_currency(char *buffer) {
	return (Currency) 0;
}

