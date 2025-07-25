
#include "utils.h"
#include "io.h"


int main(void) {
	Currency total = 0;
	for (;;) {
		print_currency("=> %s\n?> ", total);
		total += scan_currency();
	}
	exit(0);
}

