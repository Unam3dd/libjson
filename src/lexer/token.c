#include "libjson.h"

///////////////////////////////////////
//
//             INCLUDES
//
//////////////////////////////////////

#include <string.h>

///////////////////////////////////////
//
//             IS_STRING
//
//////////////////////////////////////

static inline json_bool_t	token_is_string(const char *str)
{
	if (!str) return (FALSE);
	
	char	*tmp = NULL;

	if (*str != '"')
		return (FALSE);

	tmp = strchr(str + 1, '"');

	if (!tmp)
		return (FALSE);

	//*pos = *pos + (tmp - str) + 1;

	return (TRUE);
}

token_type_t	next_token(lexer_t *lexer)
{
	if (!lexer) return (TOKEN_ERR);

	lexer->pos += strspn(lexer->buf + lexer->pos, "  \t\r\n");

	switch (*(lexer->buf + lexer->pos)) {

		case TOKEN_LBRACE:
			lexer->pos++;
			return (TOKEN_LBRACE);

		case TOKEN_RBRACE:
			lexer->pos++;
			return (TOKEN_RBRACE);

		case TOKEN_LBRACKET:
			lexer->pos++;
			return (TOKEN_LBRACKET);

		case TOKEN_RBRACKET:
			lexer->pos++;
			return (TOKEN_RBRACKET);
		
		case TOKEN_COLON:
			lexer->pos++;
			return (TOKEN_COLON);

		case TOKEN_COMMA:
			lexer->pos++;
			return (TOKEN_COMMA);

		case TOKEN_EOF:
			return (TOKEN_EOF);

		default:
			break;
	}

	if (token_is_string((const char *)(lexer->buf + lexer->pos)))
		return (TOKEN_STRING);
	
	return (TOKEN_ERR);
}

///////////////////////////////////////
//
//           PRINT TOKEN TYPE
//
//////////////////////////////////////

const char		*get_string_token_type(const token_type_t type)
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
		{ TOKEN_STRING, "TOKEN_STRING"     },
		{ TOKEN_NUMBER, "TOKEN_NUMBER"     },
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
