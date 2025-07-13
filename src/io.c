#include <stdio.h>


char *currency_to_str(char *buffer, unsigned long amount) {
	sprintf(buffer, "%'d.%02d", amount / 100, amount % 100);
	return buffer;
}

