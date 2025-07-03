#include <stdio.h>
#include "libjson.h"
#include <string.h>
#include <assert.h>

int main(void)
{
	json_ast_t	ast = { NULL, NULL, 0};
	json_node_t *ptr = NULL;

	assert(json_ast_free_all(&ast) == JSON_OK);
	assert(json_node_free(&ptr) == JSON_OK);

	return (0);
}
