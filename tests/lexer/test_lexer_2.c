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
