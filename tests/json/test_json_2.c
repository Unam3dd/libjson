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

	assert(ast.head == NULL);
	assert(ast.tail == NULL);
	assert(ast.count == 0);

	json_ast_node_push(&ast, first);

	assert(ast.head == first);
	assert(ast.tail == first);
	assert(!strcmp(ast.head->key,ast.tail->key));
	assert(ast.head->next == NULL);
	assert(ast.tail->next == NULL);
	assert(ast.head->prev == NULL);
	assert(ast.tail->prev == NULL);
	assert(ast.count == 1);

	json_ast_node_push(&ast, second);

	assert(ast.head == second);
	assert(ast.tail == first);
	assert(ast.count == 2);

	assert(ast.head->next == first);
	assert(ast.head->next->prev == second);
	assert(ast.tail->prev == second);

	json_ast_node_push(&ast, third);

	assert(ast.head == third);
	assert(ast.tail == first);
	assert(ast.count == 3);

	assert(ast.head->next == second);
	assert(ast.head->next->next == first);
	assert(ast.tail->prev == second);
	assert(ast.tail->prev->prev == third);

	json_ast_node_pop(&ast);

	assert(ast.head == second);
	assert(ast.head->next == first);
	assert(ast.head->prev == NULL);
	assert(ast.tail->prev == second);
	assert(ast.tail->next == NULL);
	assert(ast.tail->prev->next == first);
	assert(ast.tail == first);
	assert(ast.count == 2);

	json_ast_node_pop(&ast);

	assert(ast.head == first);
	assert(ast.tail == first);
	assert(ast.head->next == NULL);
	assert(ast.head->prev == NULL);
	assert(ast.tail->prev == NULL);
	assert(ast.tail->next == NULL);
	assert(ast.count == 1);

	json_ast_node_pop(&ast);

	assert(ast.head == NULL);
	assert(ast.tail == NULL);
	assert(ast.count == 0);

	return (0);
}
