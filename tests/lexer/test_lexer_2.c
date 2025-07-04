#include "libjson.h"
#include <assert.h>

int main(void)
{
	assert(token_is_number("0") == TRUE);
	assert(token_is_number("123") == TRUE);
	assert(token_is_number("-12.34") == TRUE);
	assert(token_is_number("1e9") == TRUE);
	assert(token_is_number("1.2e-10") == TRUE);
	assert(token_is_number("-0") == TRUE);
	assert(token_is_number("-123") == TRUE);
	assert(token_is_number("0.5") == TRUE);
	assert(token_is_number("-0.5") == TRUE);
	assert(token_is_number("10.25") == TRUE);
	assert(token_is_number("123e5") == TRUE);
	assert(token_is_number("123E5") == TRUE);
	assert(token_is_number("123e+5") == TRUE);
	assert(token_is_number("123e-5") == TRUE);
	assert(token_is_number("123.456e+78") == TRUE);

	assert(token_is_number(NULL) == FALSE);
	assert(token_is_number("") == FALSE);
	assert(token_is_number("01") == FALSE);
	assert(token_is_number(".5") == FALSE);
	assert(token_is_number("1.") == FALSE);
	assert(token_is_number("1e") == FALSE);
	assert(token_is_number(".") == FALSE);
	assert(token_is_number("e10") == FALSE);
	assert(token_is_number(".1") == FALSE);
	assert(token_is_number("00") == FALSE);
	assert(token_is_number("1e") == FALSE);
	assert(token_is_number("1e+") == FALSE);
	assert(token_is_number("1e-") == FALSE);
	assert(token_is_number("1.2.3") == FALSE);
	assert(token_is_number("1a") == FALSE);
	assert(token_is_number("1e10e10") == FALSE);
	assert(token_is_number("--1") == FALSE);

	return (0);
}
