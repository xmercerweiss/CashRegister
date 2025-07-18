#include <string.h>
#include <locale.h>

#include "unity/unity.h"
#include "utils.h"
#include "io.h"


static char buffer[MAX_BUFFER_SIZE];

// TODO Replace separate test data arrays with 1 array of structs
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

	// TODO Move data validation into separate function
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

void test_sprint_currency_returns_formatted_str(void) {
	Currency test_amount;
	char *expected_str;
	char *actual_str;

	for (int i = 0; i < TEST_VALS_LEN; i++) {
		test_amount = VALID_CURRENCY_VALS[i];
		expected_str = VALID_CURRENCY_STRS[i];
		actual_str = sprint_currency(buffer, MAX_BUFFER_SIZE, "%s", test_amount);
		TEST_ASSERT_EQUAL_STRING(expected_str, actual_str);
	}
}

void test_fprint_currency_prints_formatted_str(void) {
	Currency test_amount;
	char *expected_str;
	char *actual_str;
	FILE *test_file = fopen()
	// TODO finish this test T_T

	for (int i = 0; i < TEST_VALS_LEN; i++) {
		test_amount = VALID_CURRENCY_VALS[i];
		expected_str = VALID_CURRENCY_STRS[i];
		fprint_currency(test_file, "%s", test_amount);
		TEST_ASSERT_EQUAL_STRING(expected_str, actual_str);
	}
}

int main(void) {
	s_init();
	UNITY_BEGIN();
	RUN_TEST(test_sprint_currency_returns_formatted_str);
	RUN_TEST(test_fprint_currency_prints_formatted_str);
	return UNITY_END();
}

