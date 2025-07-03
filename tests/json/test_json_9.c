#include "libjson.h"
#include <stdlib.h>
#include <assert.h>

int main(void)
{
	json_ast_t	ast = { NULL, NULL, 0 };
	json_node_t	*tmp = NULL;

	json_ast_node_arena(&ast, 10);

	tmp = ast.head;

	while (tmp) {
		json_node_show(tmp);
		tmp = tmp->next;
	}

	json_ast_free_all(&ast);

	assert(ast.head == NULL);
	assert(ast.tail == NULL);
	assert(ast.count == 0);

	return (0);
}
