#include "libjson.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void)
{
	json_ast_t	ast = { NULL, NULL, 0 };
	json_node_t	*tmp = json_node_new();

	tmp->key = "last";

	assert(json_ast_node_arena(&ast, 10) == JSON_OK);

	json_ast_node_push_back(&ast, tmp);

	assert(!strcmp(tmp->key, "last"));

	json_ast_free_all(&ast);

	assert(ast.head == NULL);
	assert(ast.tail == NULL);
	assert(ast.count == 0);

	return (0);
}
