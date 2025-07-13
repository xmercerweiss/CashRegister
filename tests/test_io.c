#include <string.h>
#include <locale.h>

#include "unity/unity.h"
#include "io.h"


char buffer[BUFFER_SIZE];


void setUp(void) {
	setlocale(LC_NUMERIC, "");
	strncpy(buffer, "", BUFFER_SIZE);
}

void tearDown(void) {
	
}

void test_currency_to_str_returns_formatted_str(void) {
	TEST_ASSERT_EQUAL_STRING("0.00", currency_to_str(buffer, 0));
	TEST_ASSERT_EQUAL_STRING("0.01", currency_to_str(buffer, 1));
	TEST_ASSERT_EQUAL_STRING("1.00", currency_to_str(buffer, 100));
	TEST_ASSERT_EQUAL_STRING("5.37", currency_to_str(buffer, 537));
	TEST_ASSERT_EQUAL_STRING("500.37", currency_to_str(buffer, 50037));
	TEST_ASSERT_EQUAL_STRING("5,000.37", currency_to_str(buffer, 500037));
	TEST_ASSERT_EQUAL_STRING("1,005,000.37", currency_to_str(buffer, 100500037));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_currency_to_str_returns_formatted_str);
	return UNITY_END();
}

