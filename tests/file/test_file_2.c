#include "libjson.h"
#include <stddef.h>
#include <assert.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	json_file_t	file = { NULL, 0, 0 };

	assert(json_read_file(NULL, NULL) == JSON_ERR);
	
	assert(json_read_file(&file, NULL) == JSON_ERR);
	
	assert(json_read_file(NULL, av[1]) == JSON_ERR);
	
	assert(json_read_file(&file, av[1]) == JSON_ERR);

	return (0);
}
