#ifndef LIBJSON_H
#define LIBJSON_H

#pragma once

///////////////////////////////////////
//
//            INCLUDES
//
//////////////////////////////////////

#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

///////////////////////////////////////
//
//            TYPEDEFS
//
//////////////////////////////////////

typedef enum e_json_bool_t 
{
	FALSE,
	TRUE
} json_bool_t;

typedef enum e_json_flag_t
{
	BLOCK = 1 << 0,
	ARENA = 1 << 1
} json_flag_t;

typedef struct s_lexer_t 		json_lexer_t;
typedef json_lexer_t			json_file_t;
typedef json_lexer_t			json_buf_t;

typedef struct s_json_node_t	json_node_t;
typedef struct s_json_parse_t	json_parse_t;
typedef struct s_json_ast_t		json_ast_t;
typedef json_node_t				json_object_t;

typedef char*					json_string_t;
typedef const char*				json_cstring_t;

typedef long**					json_array_number_t;
typedef void*					json_array_t;
typedef json_string_t**			json_array_str_t;
typedef json_cstring_t**		json_array_cstr_t;
typedef json_node_t**			json_array_object_t;
typedef json_array_t*			json_array_array_t;
typedef json_bool_t**			json_array_bool_t;

typedef long					json_number_t;
typedef double					json_float_number_t;

typedef struct s_json_type_str_t	json_type_str_t;
typedef struct s_json_token_str_t		token_str_t;

///////////////////////////////////////
//
//             ENUM
//
//////////////////////////////////////

typedef enum e_json_token_type_t {
	TOKEN_ERR = 0x7F,
	TOKEN_LBRACE = '{',    	// {
	TOKEN_RBRACE = '}',   	//  }
	TOKEN_LBRACKET = '[', 	//  [
	TOKEN_RBRACKET = ']', 	//  ]
	TOKEN_COLON = ':', 		// :
	TOKEN_COMMA = ',',		// ,
	TOKEN_STRING = '"',		// String
	TOKEN_NUMBER = 1,		// Number
	TOKEN_EOF = 0,			// End of file
} json_token_type_t;

typedef enum e_json_type_t {
	JSON_NULL,
	JSON_BOOL, 		// true or false
	JSON_OBJECT,	// { "name": "toto", "age": 3 }
	JSON_ARRAY,		// [0, 1, 2]
	JSON_STRING,	// "Simple string"
	JSON_NUMBER		// 2, 3, -12
} json_type_t;

typedef enum e_json_status_t {
	JSON_OK,
	JSON_ERR
} json_status_t;

///////////////////////////////////////
//
//            STRUCTS
//
//////////////////////////////////////

struct s_json_token_str_t
{
	json_token_type_t	type;
	const char			*str;
};

struct s_json_type_str_t
{
	const char		*str;
	json_type_t		type;
};

struct s_lexer_t
{
	const char			*buf;
	size_t				pos;
	ssize_t				size;
};

struct s_json_node_t
{
	json_cstring_t	key;
	
	union {

		json_object_t			*obj;
		
		union {
			json_array_array_t	arr;
			json_array_object_t	arr_obj;
			json_array_cstr_t	arr_cstr;
			json_array_str_t	arr_str;
			json_array_number_t	arr_nbr;
			json_array_bool_t	arr_bool;
		};

		json_cstring_t			cstr;
		json_string_t			str;
		json_number_t			nbr;
		json_float_number_t		fnbr;
		json_bool_t				boolean;

	} value;

	json_node_t			*next;
	json_node_t			*prev;
	json_node_t			*mptr;
	json_flag_t			flag;
	json_type_t			type;
};

struct s_json_ast_t
{
	json_node_t	*head;
	json_node_t	*tail;
	uint32_t	count;
};

struct s_json_parse_t
{
	json_lexer_t	*lexer;
	json_ast_t		ast;
	uint32_t		count;
};

///////////////////////////////////////
//
//            LEXER
//
//////////////////////////////////////

const char *get_string_token_type(const json_token_type_t type);

json_bool_t			token_is_number(const char *str);
json_token_type_t	lexer_peek(json_lexer_t *lexer);
json_token_type_t	lexer_next(json_lexer_t *lexer);

///////////////////////////////////////
//
//            FILE/BUF
//
//////////////////////////////////////

json_status_t	json_read_file(json_file_t *f, const char *filename);
json_status_t	json_free_file(json_file_t *f);

static inline json_status_t	json_read_from_string(json_buf_t *buf, const char *string, size_t size) {
	
	if (!buf)
		return (JSON_ERR);

	buf->buf = string;
	buf->size = size;
	buf->pos = 0;

	return (JSON_OK);
}

///////////////////////////////////////
//
//            VERSION
//
//////////////////////////////////////

/**
* @brief libjson_version
*
*
* Return the version of libjson.
*
*
* @return Return a string which contains 
* the version of the libjson library
*/

const char	*libjson_version(void);

///////////////////////////////////////
//
//             PARSER
//
//////////////////////////////////////

json_status_t	json_parse(json_parse_t *p, json_lexer_t *l);

///////////////////////////////////////
//
//         	JSON AST
//
//////////////////////////////////////


const char  	*json_get_type_str(const json_type_t type);

json_node_t		*json_node_new(void);
json_status_t	json_ast_node_arena(json_ast_t *ast, const size_t n);
json_status_t	json_ast_node_pop(json_ast_t *ast);
json_status_t	json_ast_node_pop_back(json_ast_t *ast);
json_status_t	json_ast_free_all(json_ast_t *ast);
json_status_t	json_ast_node_push(json_ast_t *ast, json_node_t *node);
json_status_t	json_ast_node_push_back(json_ast_t *ast, json_node_t *node);
json_status_t	json_node_free(json_node_t **node);
void			json_node_show(const json_node_t *node);

#endif
