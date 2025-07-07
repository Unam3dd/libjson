#include "libjson.h"

///////////////////////////////////////
//
//             INCLUDES
//
//////////////////////////////////////

#include <string.h>

///////////////////////////////////////
//
//            STATIC
//
//////////////////////////////////////

static json_bool_t	number_bad_dot(const char *str)
{
	if (!str) return (FALSE);

	char	*ptr = strchr(str, '.');

	if (!ptr)
		return (FALSE);

	++ptr;

	return (ptr && strchr(ptr, '.') ? TRUE : FALSE);
}

///////////////////////////////////////
//
//            NUMBER
//
//////////////////////////////////////

json_bool_t token_is_number(const char *str)
{
	if (!str || !*str)
		return (FALSE);

	if (strspn(str, "-+0123456789eE.") != strlen(str))
		return (FALSE);

	if (number_bad_dot(str))
		return (FALSE);

	const char	*tmp = str;
	size_t	len = 0;

	len = strspn(str, "-");

	if (len > 1) return (FALSE);

	tmp += len;

	if (*tmp == '0') {
		len = strspn(tmp, "0");

		if (len > 1 || strspn(tmp + 1, "123456789") >= 1) return (FALSE);

		if (tmp && *(tmp + 1) != '.')
			tmp += len;

		if (!*tmp) return (TRUE);
	}

	len = strspn(tmp, "0123456789");

	if (!len) return (FALSE);

	tmp += len;

	if (*tmp == '.') {
		len = strspn(tmp, ".");

		if (len > 1 || !strspn(tmp + 1, "0123456789")) return (FALSE);

		tmp += len;
	}

	if (*tmp == 'e' || *tmp == 'E') {

		if (strspn(tmp, "eE") > 1) return (FALSE);

		len = strspn(++tmp, "-+");

		if (len > 1) return (FALSE);

		tmp += len;

		if (!strspn(tmp, "0123456789")) return (FALSE);

		if (*tmp == '0') {
			
			if (strspn(tmp, "0") > 1) return (FALSE);
			
			++tmp;
		}
		
		tmp += strspn(tmp, "0123456789");
	}

	return (TRUE);
}

/////////////////////////////////////
//
//
//			LEXER PEEK
//
//
////////////////////////////////////

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

	return (TOKEN_ERR);
}

/////////////////////////////////////
//
//
//			LEXER NEXT
//
//
////////////////////////////////////

json_token_type_t lexer_next(json_lexer_t *lexer)
{
	if (!lexer)
		return (TOKEN_ERR);

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

	return (TOKEN_ERR);
}

///////////////////////////////////////
//
//           PRINT TOKEN TYPE
//
//////////////////////////////////////

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
