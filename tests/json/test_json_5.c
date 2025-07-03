#include <stdio.h>
#include "libjson.h"
#include <string.h>
#include <assert.h>

int main(void)
{
	json_ast_t	ast = { NULL, NULL, 0};

	json_node_t	*first = json_node_new();
	json_node_t	*second = json_node_new();
	json_node_t	*third = json_node_new();

	first->key = "first";
	second->key = "second";
	third->key = "third";

	json_status_t status = json_ast_node_push_back(NULL, first);

	assert(ast.head == NULL);
	assert(ast.tail == NULL);
	assert(ast.count == 0);
	assert(status == JSON_ERR);
	
	status = json_ast_node_push_back(NULL, NULL);

	assert(status == JSON_ERR);

	status = json_ast_node_push_back(&ast, NULL);

	assert(status == JSON_ERR);

	json_node_show(first);

	json_node_free(&first);
	json_node_free(&second);
	json_node_free(&third);
	
	assert(first == NULL);
	assert(second == NULL);
	assert(third == NULL);

	return (0);
}
