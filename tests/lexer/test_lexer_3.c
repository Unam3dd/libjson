#include <assert.h>
#include "libjson.h"

int main(void)
{
	// Nouveaux tests - exposants invalides
	assert(token_is_number("1ee10") == FALSE);
	assert(token_is_number("1eE10") == FALSE);
	assert(token_is_number("1Ee10") == FALSE);
	assert(token_is_number("1EE10") == FALSE);
	assert(token_is_number("1e++10") == FALSE);
	assert(token_is_number("1e--10") == FALSE);
	assert(token_is_number("1e+-10") == FALSE);
	assert(token_is_number("1e-+10") == FALSE);
	assert(token_is_number("1e10e") == FALSE);
	assert(token_is_number("1e10.5") == FALSE);

	// Nouveaux tests - signes multiples
	assert(token_is_number("++1") == FALSE);
	assert(token_is_number("+-1") == FALSE);
	assert(token_is_number("-+1") == FALSE);
	assert(token_is_number("---1") == FALSE);
	assert(token_is_number("+++1") == FALSE);

	// Nouveaux tests - caractères non valides
	assert(token_is_number("1 ") == FALSE);
	assert(token_is_number(" 1") == FALSE);
	assert(token_is_number("1 2") == FALSE);
	assert(token_is_number("1\t") == FALSE);
	assert(token_is_number("1\n") == FALSE);
	assert(token_is_number("1x") == FALSE);
	assert(token_is_number("x1") == FALSE);
	assert(token_is_number("1@") == FALSE);
	assert(token_is_number("1#") == FALSE);
	assert(token_is_number("1$") == FALSE);
	assert(token_is_number("1%") == FALSE);
	assert(token_is_number("1&") == FALSE);
	assert(token_is_number("1*") == FALSE);
	assert(token_is_number("1()") == FALSE);
	assert(token_is_number("1[]") == FALSE);
	assert(token_is_number("1{}") == FALSE);

	// Nouveaux tests - nombres valides supplémentaires
	assert(token_is_number("9") == TRUE);
	assert(token_is_number("9.0") == TRUE);
	assert(token_is_number("0.0") == TRUE);
	assert(token_is_number("0.00") == TRUE);
	assert(token_is_number("0.123456789") == TRUE);
	assert(token_is_number("999999999") == TRUE);
	assert(token_is_number("-999999999") == TRUE);
	assert(token_is_number("1E-999") == TRUE);
	assert(token_is_number("1E+999") == TRUE);
	assert(token_is_number("1e999") == TRUE);
	assert(token_is_number("1e-999") == TRUE);
	assert(token_is_number("1e+999") == TRUE);
	
	return (0);
}
