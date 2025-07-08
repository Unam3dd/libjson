#include "libjson.h"

///////////////////////////////////////
//
//             INCLUDES
//
//////////////////////////////////////

#include <string.h>

///////////////////////////////////////
//
//            STATIC HELPERS
//
//////////////////////////////////////

/**
 * @brief Checks if a string contains multiple decimal points
 * 
 * This function validates that a string doesn't contain more than one
 * decimal point, which would make it an invalid number format.
 * 
 * @param str The string to check for multiple decimal points
 * @return TRUE if the string contains multiple decimal points, FALSE otherwise
 */
static json_bool_t	number_bad_dot(const char *str)
{
	if (!str) return (FALSE);

	char	*ptr = strchr(str, '.');

	if (!ptr)
		return (FALSE);

	++ptr;

	return (ptr && strchr(ptr, '.') ? TRUE : FALSE);
}

/**
 * @brief Validates the integer part of a JSON number and returns its length
 * 
 * This function validates the integer portion of a JSON number according to
 * JSON specification rules:
 * - Optional minus sign
 * - Single zero OR non-zero digit followed by any digits
 * - Leading zeros are not allowed (except for standalone zero)
 * 
 * @param str Pointer to the string containing the number
 * @return Length of the valid integer part, or 0 if invalid
 */
static size_t validate_integer_part(const char *str)
{
	if (!str || !*str) return (0);
	
	const char *start = str;
	
	// Handle optional minus sign
	if (*str == '-') {
		
		str++;
		
		if (!*str) return (0); // Just a sign is not valid
	}
	
	// Special case for zero
	if (*str == '0') {
		
		str++;
		
		// After zero, only '.', end of string allowed - no 'e' or 'E' directly
		if (*str && *str != '.') return (0);
		
		return (str - start);
	}
	
	// Numbers starting with 1-9
	if (*str >= '1' && *str <= '9') {
		
		// Consume all following digits
		str += strspn(str, "0123456789");
		
		return (str - start);
	}
	
	return (0);
}

/**
 * @brief Validates the fractional part of a JSON number and returns its length
 * 
 * This function validates the fractional portion of a JSON number:
 * - Must start with a decimal point
 * - Must be followed by at least one digit
 * - Can contain multiple digits after the decimal point
 * 
 * @param str Pointer to the string at the potential decimal point
 * @return Length of the valid fractional part (including the dot), or 0 if no fractional part
 */
static size_t validate_fraction_part(const char *str)
{
	if (!str || *str != '.') return (0); // No fractional part
	
	const char *start = str;
	
	str++; // Skip the '.'
	
	// Must have at least one digit after the decimal point
	if (!*str || *str < '0' || *str > '9') {
		return (0);
	}

	str += strspn(str, "0123456789");
	
	return (str - start);
}

/**
 * @brief Validates the exponent part of a JSON number and returns its length
 * 
 * This function validates the exponent portion of a JSON number:
 * - Must start with 'e' or 'E'
 * - Optional '+' or '-' sign
 * - Must be followed by at least one digit
 * - Can contain multiple digits
 * 
 * @param str Pointer to the string at the potential exponent indicator
 * @return Length of the valid exponent part, or 0 if no exponent part
 */
static size_t validate_exponent_part(const char *str)
{
	if (!str || (*str != 'e' && *str != 'E')) return (0);
	
	const char *start = str;
	str++; // Skip 'e' or 'E'
	
	// Optional sign
	if (*str == '+' || *str == '-')
		str++;
	
	// Must have at least one digit
	if (!*str || *str < '0' || *str > '9') return (0);

	str += strspn(str, "0123456789");
	
	return (str - start);
}

///////////////////////////////////////
//
//            NUMBER VALIDATION
//
//////////////////////////////////////

/**
 * @brief Validates if a string represents a valid JSON number
 * 
 * This function validates a string according to JSON number specification:
 * - Must contain only valid number characters (-+0123456789eE.)
 * - Must not contain multiple decimal points
 * - Must have valid integer part (required)
 * - May have valid fractional part (optional)
 * - May have valid exponent part (optional)
 * - Must consume the entire string
 * 
 * @param str The string to validate as a JSON number
 * @return TRUE if the string is a valid JSON number, FALSE otherwise
 */
json_bool_t token_is_number(const char *str)
{
	if (!str 
		|| !*str 
		|| strspn(str, "-+0123456789eE.") != strlen(str) 
		|| number_bad_dot(str))
		return (FALSE);
	
	const char *current = str;
	size_t len = validate_integer_part(current);
	
	if (len == 0)
		return (FALSE);
	
	current += len;
	
	// Validate fractional part (optional)
	len = validate_fraction_part(current);
	current += len;
	
	// Validate exponent part (optional)
	len = validate_exponent_part(current);
	current += len;
	
	// Check that we consumed the entire string
	return (!*current);
}

///////////////////////////////////////
//
//            LEXER OPERATIONS
//
//////////////////////////////////////

/**
 * @brief Peeks at the current token without advancing the lexer position
 * 
 * This function examines the character at the current lexer position and
 * returns the corresponding token type without modifying the lexer state.
 * Used for lookahead operations in parsing.
 * 
 * @param lexer Pointer to the lexer structure
 * @return The token type at the current position, or TOKEN_ERR if invalid
 */
json_token_type_t	lexer_peek(json_lexer_t *lexer)
{
	if (!lexer) return (TOKEN_ERR);

	switch (*(lexer->buf + lexer->pos)) {

		case '{': return (TOKEN_LBRACE);

		case '}': return (TOKEN_RBRACE);

		case '[': return (TOKEN_LBRACKET);

		case ']': return (TOKEN_RBRACKET);

		case ':': return (TOKEN_COLON);

		case ',': return (TOKEN_COMMA);

		case '"': return (TOKEN_STRING);

		case 0: return (TOKEN_EOF);

		default:
			break;
	}

	if (token_is_number(lexer->buf + lexer->pos))
		return (TOKEN_NUMBER);

	return (TOKEN_ERR);
}

/**
 * @brief Gets the next token and advances the lexer position
 * 
 * This function examines the character at the current lexer position,
 * returns the corresponding token type, and advances the lexer position
 * by one character. This is the main tokenization function.
 * 
 * @param lexer Pointer to the lexer structure
 * @return The token type at the current position, or TOKEN_ERR if invalid
 */
json_token_type_t lexer_next(json_lexer_t *lexer)
{
	if (!lexer)
		return (TOKEN_ERR);

	lexer->pos += strspn((char *)(lexer->buf + lexer->pos), " \t\r\n");

	switch (*(lexer->buf + lexer->pos)) {

		case '{':
			lexer->pos++;
			return (TOKEN_LBRACE);

		case '}':
			lexer->pos++;
			return (TOKEN_RBRACE);

		case '[':
			lexer->pos++;
			return (TOKEN_LBRACKET);

		case ']':
			lexer->pos++;
			return (TOKEN_RBRACKET);

		case ':':
			lexer->pos++;
			return (TOKEN_COLON);

		case ',':
			lexer->pos++;
			return (TOKEN_COMMA);

		case '"':
			lexer->pos++;
			return (TOKEN_STRING);

		case 0: return (TOKEN_EOF);

		default:
			break;
	}

	if (token_is_number(lexer->buf + lexer->pos))
		return (TOKEN_NUMBER);

	return (TOKEN_ERR);
}

///////////////////////////////////////
//
//           TOKEN UTILITIES
//
//////////////////////////////////////

/**
 * @brief Converts a token type enum to its string representation
 * 
 * This function provides a string representation of token types for
 * debugging and error reporting purposes. Uses an optimized lookup
 * with loop unrolling for better performance.
 * 
 * @param type The token type enum to convert
 * @return String representation of the token type, or NULL if not found
 */
const char		*get_string_token_type(const json_token_type_t type)
{
	static const token_str_t t[] = {
		{ TOKEN_ERR,    "TOKEN_ERR"        },
		{ TOKEN_COMMA,  "TOKEN_COMMA"      },
		{ TOKEN_EOF,    "TOKEN_EOF"        },
		{ TOKEN_COLON,  "TOKEN_COLON"      },
		{ TOKEN_RBRACE, "TOKEN_RBRACE"     },
		{ TOKEN_LBRACE, "TOKEN_LBRACE"     },
		{ TOKEN_LBRACKET, "TOKEN_LBRACKET" },
		{ TOKEN_RBRACKET, "TOKEN_RBRACKET" },
		{ TOKEN_STRING,   "TOKEN_STRING"   },
		{ TOKEN_NUMBER,   "TOKEN_NUMBER"   },
	};

	// Loop unrolling for better performance
	for (uint32_t i = 0; i < sizeof(t)/sizeof(token_str_t); i += 5) {

		if (t[i].type == type)
			return (t[i].str);

		if (t[i+1].type == type)
			return (t[i+1].str);

		if (t[i+2].type == type)
			return (t[i+2].str);

		if (t[i+3].type == type)
			return (t[i+3].str);

		if (t[i+4].type == type)
			return (t[i+4].str);
	}

	return (NULL);
}
