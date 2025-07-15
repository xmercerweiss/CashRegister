#include <string.h>
#include <locale.h>

#include "unity/unity.h"
#include "utils.h"
#include "io.h"


static char buffer[MAX_BUFFER_SIZE];

static Currency VALID_CURRENCY_VALS[] = {
 		  	0,
	        1,
	      100,
	      530,
	      537,
	    50037,
	   500037,
	100500037,
};


static char *VALID_CURRENCY_STRS[] = {
	       "$0",
	       "$0.01",
	       "$1",
	       "$5.30",
	       "$5.37",
	     "$500.37",
	   "$5,000.37",
   "$1,005,000.37"
};

static const int TEST_VALS_LEN = sizeof(VALID_CURRENCY_VALS) / sizeof(Currency);


// Run once at startup
static void s_init(void) {
	// Locale must be set for allowance of %'d format specifier used in io.h
	setlocale(LC_NUMERIC, "");

	// Verify that all test data arrays have the same size
	int test_strs_len = sizeof(VALID_CURRENCY_STRS) / sizeof(void*);
	if (test_strs_len < TEST_VALS_LEN) { 
		ERROR("Missing test data strings");
	}
	else if (test_strs_len > TEST_VALS_LEN) {
		ERROR("Missing test data values");
	}
}

// Run before each test
void setUp(void) {
	strncpy(buffer, "", MAX_BUFFER_SIZE);
}

// Run after each test
void tearDown(void) {
	
}

void test_currency_to_str_returns_formatted_str(void) {
	Currency test_amount;
	char *expected_str;
	char *actual_str;

	for (int i = 0; i < TEST_VALS_LEN; i++) {
		test_amount = VALID_CURRENCY_VALS[i];
		expected_str = VALID_CURRENCY_STRS[i];
		actual_str = currency_to_str(buffer, MAX_BUFFER_SIZE, test_amount);
		TEST_ASSERT_EQUAL_STRING(expected_str, actual_str);
	}
}

int main(void) {
	s_init();
	UNITY_BEGIN();
	RUN_TEST(test_currency_to_str_returns_formatted_str);
	return UNITY_END();
}

