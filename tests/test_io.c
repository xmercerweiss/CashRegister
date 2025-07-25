#include <string.h>
#include <locale.h>

#include "unity/unity.h"
#include "testutils.h"
#include "utils.h"
#include "io.h"


#define NULL_DATUM {0, NULL}
#define INV_CURR   0


static const TestDatum VALID_CURR_INPS[] = {
	// Formatted output is valid input
	{0, "$0"},
	{1, "$0.01"},
	{100, "$1.00"},
	{530, "$5.30"},
	{537, "$5.37"},
	{50037, "$500.37"},
	{500037, "$5,000.37"},
	{100500037, "$1,005,000.37"},
	// Unformatted strings are also valid
	{0, "0"},
	{1, "0.01"},
	{100, "1"},
	{530, "5.3"},
	{537, "5.37"},
	{50037, "500.37"},
	{500037, "5000.37"},
	{100500037, "1005000.37"},
	// Test optional quantities
	{0, "$0x0"},
	{0, "$0x1"},
	{0, "$1x0"},
	{100, "$1x1"}, 
	{200, "$2x1"},
	{200, "$1x2"},
	{400, "$2x2"},
	{1000, "$5x2"},
	{4200, "$6x7"},
	{100000, "$20x5"},
	{2721, "$9.07x3"},
	{440, "$1.10x4"},
	{5500, "$5.50x10"},
	{132000, "$220x6"},
	NULL_DATUM
};

static const TestDatum VALID_CURR_OUTS[] = {
	{0, "$0.00"},
	{1, "$0.01"},
	{100, "$1.00"},
	{530, "$5.30"},
	{537, "$5.37"},
	{50037, "$500.37"},
	{500037, "$5,000.37"},
	{100500037, "$1,005,000.37"},
	NULL_DATUM
};

static const TestDatum INVALID_CURR_INPS[] = {
	{INV_CURR, ""},
	{INV_CURR, "Hello"},
	{INV_CURR, "Goodbye7"},
	{INV_CURR, "H7J8K9"},
	{INV_CURR, "127.0.0.1"},
	NULL_DATUM
};


static char buffer[MAX_BUFFER_SIZE];


// Run once at startup
static void s_init(void) {
	// Locale must be set for allowance of %'d format specifier used in io.h
	setlocale(LC_NUMERIC, "");
}

// Run before each test
void setUp(void) {
	// Fill buffer with null values
	strncpy(buffer, "", MAX_BUFFER_SIZE);
}

// Run after each test
void tearDown(void) {
	
}

void test_sprint_currency_returns_formatted_str(void) {
	const TestDatum *datum;
	char *returned;
	for (datum = VALID_CURR_OUTS; datum->string != NULL; datum++) {
		returned = sprint_currency(buffer, MAX_BUFFER_SIZE, "%s", datum->value);
		TEST_ASSERT_EQUAL_STRING(datum->string, returned);
	}
}

void test_sscan_currency_returns_correct_value(void) {
	const TestDatum *datum;
	Currency returned;
	for (datum = VALID_CURR_INPS; datum->string != NULL; datum++) {
		returned = sscan_currency(datum->string);
		printf("%s: %lu\n", datum->string, returned);
		TEST_ASSERT_EQUAL_UINT(datum->value, returned);
	}
}

void test_sscan_currency_handles_invalid_strs(void) {
	const TestDatum *datum;
	Currency returned;
	for (datum = INVALID_CURR_INPS; datum->string != NULL; datum++) {
		returned = sscan_currency(datum->string);
		TEST_ASSERT_EQUAL_UINT(datum->value, returned);
	}
}

void test_fscan_currency_returns_correct_value(void) {
	const TestDatum *datum;
	Currency returned;
	int i = 0;
	for (datum = VALID_CURR_INPS; datum->string != NULL; datum++) {
		FILE *temp = tmpfile();
		TEST_ASSERT_NOT_NULL(temp);
		fprintf(temp, datum->string);
		rewind(temp);
		returned = fscan_currency(temp);
		fclose(temp);
		temp = NULL;
		TEST_ASSERT_EQUAL_UINT(datum->value, returned);
	}
}

int main(void) {
	s_init();
	UNITY_BEGIN();
	RUN_TEST(test_sprint_currency_returns_formatted_str);
	RUN_TEST(test_sscan_currency_returns_correct_value);
	RUN_TEST(test_sscan_currency_handles_invalid_strs);
	RUN_TEST(test_fscan_currency_returns_correct_value);
	return UNITY_END();
}

