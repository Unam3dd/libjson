#include "libjson.h"
#include <assert.h>

int main(void)
{
	// Tests existants - nombres valides
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

	// Tests existants - nombres invalides
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

	// Nouveaux tests - nombres avec zéros en tête invalides
	assert(token_is_number("001") == FALSE);
	assert(token_is_number("00123") == FALSE);
	assert(token_is_number("000") == FALSE);
	assert(token_is_number("0123") == FALSE);
	assert(token_is_number("0001.5") == FALSE);
	assert(token_is_number("-00") == FALSE);
	assert(token_is_number("-001") == FALSE);
	assert(token_is_number("-0123") == FALSE);

	// Nouveaux tests - nombres avec points décimaux multiples
	assert(token_is_number("1..2") == FALSE);
	assert(token_is_number("1.2.3.4") == FALSE);
	assert(token_is_number("..1") == FALSE);
	assert(token_is_number("1..") == FALSE);
	assert(token_is_number("1.2..3") == FALSE);

	// Nouveaux tests - exposants invalides
	assert(token_is_number("1ee10") == FALSE);

	return (0);
}
