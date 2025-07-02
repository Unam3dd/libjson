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

	json_ast_node_push_back(&ast, first);

	assert(ast.head == first);
	assert(ast.head->next == NULL);
	assert(ast.head->prev == NULL);
	assert(ast.tail == first);
	assert(ast.tail->next == NULL);
	assert(ast.tail->prev == NULL);
	assert(ast.count == 1);
	
	json_ast_node_push_back(&ast, second);

	assert(ast.head == first);
	assert(ast.head->next == second);
	assert(ast.head->prev == NULL);
	assert(ast.head->next->next == NULL);
	assert(ast.head->next->prev == first);
	assert(ast.tail != ast.head);
	assert(ast.tail == second);
	assert(ast.tail->prev == first);
	assert(ast.tail->next == NULL);
	assert(ast.count == 2);
	
	json_ast_node_push_back(&ast, third);

	assert(ast.count == 3);
	assert(ast.head != ast.tail);
	assert(ast.head == first);
	assert(ast.head->next == second);
	assert(ast.head->prev == NULL);
	assert(ast.head->next->prev == first);
	assert(ast.head->next->next == third);
	assert(ast.head->next->next->prev == second);
	assert(ast.head->next->next->prev->prev == first);
	assert(ast.tail == third);
	assert(ast.tail->next == NULL);
	assert(ast.tail->prev == second);
	assert(ast.tail->prev->prev == first);
	assert(ast.tail->prev->next == third);
	assert(ast.tail->prev->prev->next == second);

	json_node_free(&first);
	json_node_free(&second);
	json_node_free(&third);

	return (0);
}
