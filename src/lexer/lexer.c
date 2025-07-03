#include "libjson.h"

///////////////////////////////////////
//
//             INCLUDES
//
//////////////////////////////////////

#include <string.h>

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

json_status_t	lexer_next(json_lexer_t *lexer)
{
	if (!lexer) return (JSON_ERR);

	return (JSON_OK);
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
