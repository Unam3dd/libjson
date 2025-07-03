#include "libjson.h"
#include <string.h>
#include <assert.h>

int main(void)
{
	assert(!strcmp("JSON_NULL", json_get_type_str(JSON_NULL)));
	assert(!strcmp("JSON_BOOL", json_get_type_str(JSON_BOOL)));
	assert(!strcmp("JSON_OBJECT", json_get_type_str(JSON_OBJECT)));
	assert(!strcmp("JSON_ARRAY", json_get_type_str(JSON_ARRAY)));
	assert(!strcmp("JSON_STRING", json_get_type_str(JSON_STRING)));
	assert(!strcmp("JSON_NUMBER", json_get_type_str(JSON_NUMBER)));
	
	assert(json_get_type_str(-2) == NULL);
	assert(json_get_type_str(JSON_NUMBER+1) == NULL);
	assert(json_get_type_str(-1) == NULL);
	assert(json_get_type_str(0x7FFFFFFF) == NULL);
	assert(json_get_type_str(0xFFFFFFFF) == NULL);
	assert(json_get_type_str(0x80000000) == NULL);
	assert(json_get_type_str(0x81000000) == NULL);
	assert(json_get_type_str(0x7FFFFFFF) == NULL);
	assert(json_get_type_str(~-1) != NULL);
	
	return (0);
}
