
#include "libjson.h"

///////////////////////////////////////
//
//             INCLUDES
//
//////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <unistd.h>

/////////////////////////////////////
//
//
//			STATIC 
//
//
////////////////////////////////////

static const char	*json_parse_string(json_lexer_t *lexer)
{
	if (!lexer || !lexer->size) return (NULL);

	char *tmp = (char *)(lexer->buf + lexer->pos);
	char *save = tmp;

	if (tmp && *tmp == '"')
		tmp++;

	tmp = strchr((char *)lexer->buf + lexer->pos, '"');

	if (!tmp || (tmp && strspn(tmp, "\"") > 1))
		return (NULL);

	if (*tmp != '"')
		return (NULL);
	
	*tmp = 0;

	lexer->pos += (uint64_t)tmp - (uint64_t)(lexer->buf + lexer->pos) + 1;

	return (save);
}

///////////////////////////////////////
//
//             PARSER
//
//////////////////////////////////////

json_status_t	json_parse(json_parse_t *p, json_lexer_t *l)
{
	if (!p || !l || !l->buf)
		return (JSON_ERR);

	if (!l->size)
		return (JSON_OK);

	memset(p, 0, sizeof(json_parse_t));

	json_token_type_t	token;
	char	*id = NULL;

	while ((token = lexer_next(l)) != TOKEN_EOF) {
		
		printf("token: %s\n", get_string_token_type(token));

		switch (token) {

			case TOKEN_STRING:
				id = (char *)json_parse_string(l);
				printf("ID: %s\n", id);
				break;

			case TOKEN_LBRACE:
				break;

			case TOKEN_ERR:
			default:
				return (JSON_ERR);
		}
	}

	return (JSON_OK);
}
