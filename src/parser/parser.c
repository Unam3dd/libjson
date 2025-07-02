
#include "libjson.h"

///////////////////////////////////////
//
//             INCLUDES
//
//////////////////////////////////////

#include <string.h>

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

	return (JSON_OK);
}
