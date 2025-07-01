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

typedef struct s_lexer_t 		lexer_t;
typedef struct s_json_node_t	json_node_t;
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

typedef struct s_token_str_t	token_str_t;

///////////////////////////////////////
//
//             ENUM
//
//////////////////////////////////////

typedef enum e_token_type_t {
	TOKEN_ERR = 0x7F,
	TOKEN_LBRACE = '{',    	// {
	TOKEN_RBRACE = '}',   	//  }
	TOKEN_LBRACKET = '[', 	//  [
	TOKEN_RBRACKET = ']', 	//  ]
	TOKEN_COLON = ':', 		// :
	TOKEN_COMMA = ',',		// ,
	TOKEN_STRING = 1,		// String
	TOKEN_NUMBER = 2,		// Number
	TOKEN_EOF = 0,			// End of file
} token_type_t;

typedef enum e_json_type_t {
	JSON_INVALID,
	JSON_OBJECT,	// { "name": "toto", "age": 3 }
	JSON_ARRAY,		// [0, 1, 2]
	JSON_STRING,	// "Simple string"
	JSON_NUMBER,	// 2, 3, -12
	JSON_BOOL		// true or false
} json_type_t;

typedef enum e_json_flag_t {
	ON_STACK	= 0,
	ON_HEAP		= 1 << 0,
} json_flag_t;

///////////////////////////////////////
//
//            STRUCTS
//
//////////////////////////////////////

struct s_token_str_t
{
	token_type_t	type;
	const char		*str;
};

struct s_lexer_t
{
	const char	*buf;
	size_t		pos;
	ssize_t		size;
};

struct s_json_node_t
{
	json_cstring_t	key;
	
	union {

		json_object_t				*obj;
		
		union {
			json_array_array_t	arr;
			json_array_object_t	arr_obj;
			json_array_cstr_t	arr_cstr;
			json_array_str_t	arr_str;
			json_array_number_t	arr_nbr;
			json_array_bool_t	arr_bool;
		};
		
		json_cstring_t	cstr;
		json_string_t	str;
		json_number_t	nbr;
		json_bool_t		boolean;

	} value;

	json_node_t	*next;
	json_node_t	*prev;
	json_type_t	type;
	json_flag_t	flag;
};

///////////////////////////////////////
//
//            ARENA
//
//////////////////////////////////////


///////////////////////////////////////
//
//            LEXER
//
//////////////////////////////////////

const char		*get_string_token_type(const token_type_t type);

token_type_t	next_token(lexer_t *lexer);

///////////////////////////////////////
//
//            AST
//
//////////////////////////////////////


///////////////////////////////////////
//
//            FILE
//
//////////////////////////////////////

int	json_read_file(lexer_t *l, const char *filename);

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

#endif
