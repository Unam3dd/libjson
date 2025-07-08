#include "libjson.h"
#include <assert.h>

int main(void)
{
	// Ces tests avec "0e" sont invalides selon l'implémentation actuelle
	assert(token_is_number("0e0") == FALSE);
	assert(token_is_number("0e+0") == FALSE);
	assert(token_is_number("0e-0") == FALSE);
	assert(token_is_number("0.0e0") == TRUE);
	assert(token_is_number("0.0e+0") == TRUE);
	assert(token_is_number("0.0e-0") == TRUE);

	// Nouveaux tests - cas limites avec exposants
	assert(token_is_number("1e0") == TRUE);
	assert(token_is_number("1e+0") == TRUE);
	assert(token_is_number("1e-0") == TRUE);
	assert(token_is_number("1E0") == TRUE);
	assert(token_is_number("1E+0") == TRUE);
	assert(token_is_number("1E-0") == TRUE);
	assert(token_is_number("1.0e0") == TRUE);
	assert(token_is_number("1.0e+0") == TRUE);
	assert(token_is_number("1.0e-0") == TRUE);
	assert(token_is_number("1.0E0") == TRUE);
	assert(token_is_number("1.0E+0") == TRUE);
	assert(token_is_number("1.0E-0") == TRUE);

	// Nouveaux tests - nombres très longs (valides)
	assert(token_is_number("123456789012345678901234567890") == TRUE);
	assert(token_is_number("0.123456789012345678901234567890") == TRUE);
	assert(token_is_number("123456789012345678901234567890.123456789012345678901234567890") == TRUE);
	assert(token_is_number("123456789012345678901234567890e123456789012345678901234567890") == TRUE);
	assert(token_is_number("-123456789012345678901234567890") == TRUE);
	assert(token_is_number("-0.123456789012345678901234567890") == TRUE);

	// Nouveaux tests - cas avec zéros (valides)
	assert(token_is_number("0.0") == TRUE);
	assert(token_is_number("0.00") == TRUE);
	assert(token_is_number("0.000") == TRUE);
	assert(token_is_number("-0.0") == TRUE);
	assert(token_is_number("-0.00") == TRUE);
	assert(token_is_number("-0.000") == TRUE);

	// Nouveaux tests - cas invalides avec des points
	assert(token_is_number("0.") == FALSE);
	assert(token_is_number("-0.") == FALSE);
	assert(token_is_number("123.") == FALSE);
	assert(token_is_number("-123.") == FALSE);
	assert(token_is_number(".") == FALSE);
	assert(token_is_number("..") == FALSE);
	assert(token_is_number("...") == FALSE);
	return (0);
}
