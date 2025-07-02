#include "libjson.h"

///////////////////////////////////////
//
//          INCLUDES
//
//////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////
//
//             NEW
//
//////////////////////////////////////

json_node_t	*json_node_new(void)
{
	return (calloc(sizeof(json_node_t), 1));
}

///////////////////////////////////////
//
//            RESERVE
//
//////////////////////////////////////

json_node_t	*json_node_reserve(const size_t n)
{
	return (calloc(sizeof(json_node_t), n));
}

///////////////////////////////////////
//
//           FREE ALL
//
//////////////////////////////////////

json_status_t	json_ast_free_all(json_ast_t *ast)
{
	if (!ast) return (JSON_ERR);

	json_node_t	*tmp = ast->head;
	json_node_t	*next = NULL;

	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}

	ast->tail = NULL;
	ast->count = 0;

	return (JSON_OK);
}

///////////////////////////////////////
//
//            FREE
//
//////////////////////////////////////

json_status_t json_node_free(json_node_t **node)
{
	if (!node)
		return (JSON_ERR);
	
	free(*node);
	
	*node = NULL;

	return (JSON_OK);
}

///////////////////////////////////////
//
//            PUSH
//
//////////////////////////////////////

json_status_t	json_ast_node_push(json_ast_t *ast, json_node_t *node)
{
	if (!ast || !node)
		return (JSON_ERR);

	json_node_t	*next = NULL;

	node->prev = NULL;

	if (!ast->head) {
		node->next = NULL;
		ast->head = node;
		ast->tail = node;
		ast->count++;
		return (JSON_OK);
	}

	if (ast->head)
		next = ast->head;

	if (next)
		next->prev = node;

	node->next = next;

	ast->head = node;
	
	// Warning: this is not atomic
	ast->count++;

	return (JSON_OK);
}

///////////////////////////////////////
//
//            	POP
//
//////////////////////////////////////

json_status_t	json_ast_node_pop(json_ast_t *ast)
{
	if (!ast)
		return (JSON_ERR);

	json_node_t	*next = NULL;

	if (ast->head)
		next = ast->head->next;

	if (next)
		next->prev = NULL;

	free(ast->head);
	
	ast->head = next;

	if (!next)
		ast->tail = NULL;
	
	// Warning: this is not atomic
	ast->count--;

	return (JSON_OK);
}

///////////////////////////////////////
//
//           PUSH BACK
//
//////////////////////////////////////

json_status_t	json_ast_node_push_back(json_ast_t *ast, json_node_t *node)
{
	if (!ast || !node)
		return (JSON_ERR);

	node->next = NULL;

	if (!ast->tail) {
		node->prev = NULL;
		ast->head = node;
		ast->tail = node;
		ast->count++;
		return (JSON_OK);
	}

	node->prev = ast->tail;
	ast->tail->next = node;
	ast->tail = node;
	
	// Warning: this is not atomic
	ast->count++;

	return (JSON_OK);
}

///////////////////////////////////////
//
//         POP BACK
//
//////////////////////////////////////

json_status_t	json_ast_node_pop_back(json_ast_t *ast)
{
	if (!ast)
		return (JSON_ERR);

	json_node_t	*prev = NULL;

	if (ast->tail)
		prev = ast->tail->prev;

	if (prev)
		prev->next = NULL;

	free(ast->tail);
	
	ast->tail = prev;

	if (!prev)
		ast->head = NULL;

	// Warning: this is not atomic
	ast->count--;

	return (JSON_OK);
}

///////////////////////////////////////
//
//           SHOW NODES
//
//////////////////////////////////////

void	json_node_show(const json_node_t *node)
{
	printf(
			"Node Address: %p\n"
			"Node Key: %s\n"
			"Node Type: %s\n"
			"Next Node: %p\n"
			"Prev Node: %p\n",
			(const void *)node, 
			(const char *)node->key,
			(const char*)get_string_token_type((const token_type_t)node->type),
			(const void *)node->next,
			(const void*)node->prev
		);
}
