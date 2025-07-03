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
	json_node_t	*m = calloc(sizeof(json_node_t), 1);

	if (!m) return (NULL);

	m->mptr = m;
	m->flag |= BLOCK;
	
	return (m);
}

///////////////////////////////////////
//
//            RESERVE
//
//////////////////////////////////////

json_status_t	json_ast_node_arena(json_ast_t *ast, const size_t n)
{
	if (!ast || (ast->count + n) >= 0xFFFFFFFFFF)
		return (JSON_ERR);

	json_node_t	*memory = calloc(sizeof(json_node_t), n);
	json_node_t	*save = NULL;

	if (!memory)
		return (JSON_ERR);

	save = ast->tail;

	memory[0].mptr = memory;

	for (size_t i = 0; i < n; i++) {

		memory[i].flag |= ARENA;

		if (json_ast_node_push_back(ast, &memory[i]) == JSON_ERR) {
			ast->tail = save;
			free(memory);
			return (JSON_ERR);
		}
	}

	ast->count += n;

	return (JSON_OK);
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

		if (!tmp->mptr)
			continue ;

		next = tmp->next;

		while (next && !next->mptr)
			next = next->next;

		free(tmp);

		tmp = next;
	}

	ast->tail = NULL;
	ast->head = NULL;
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
	if (!ast || (ast->head && ast->head->flag & ARENA))
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
	
	ast->count++;

	return (JSON_OK);
}

///////////////////////////////////////
//
//         POP BACK BLOCK
//
//////////////////////////////////////

json_status_t	json_ast_node_pop_back(json_ast_t *ast)
{
	if (!ast || (ast->tail && ast->tail->flag & ARENA))
		return (JSON_ERR);

	if (!ast->tail)
		return (JSON_OK);

	json_node_t	*prev = NULL;

	if (ast->tail->prev)
		prev = ast->tail->prev;

	if (prev)
		prev->next = NULL;

	free(ast->tail);

	if (!prev)
		ast->head = NULL;

	ast->tail = prev;
	
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
	if (!node)
		return ;

	printf(
			"Node Address: %p\n"
			"Node Key: %s\n"
			"Node Type: %s\n"
			"Next Node: %p\n"
			"Prev Node: %p\n\n",
			(const void *)node, 
			(const char *)node->key,
			json_get_type_str(node->type),
			(const void *)node->next,
			(const void*)node->prev
		);
}
