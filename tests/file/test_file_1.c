#include "libjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int ac, char **av)
{
	if (ac != 2) {
		printf("usage %s: <json_file>\n", av[0]);
		return (1);
	}

	json_file_t	file = { NULL, 0, 0 };

	printf("File to be read: %s\n", av[1]);

	assert(json_read_file(&file, av[1]) == JSON_OK);

	// Don't omit to free memory !
	free((void *)file.buf);

	file.buf = NULL;
	file.size = file.pos = 0;
	
	return (0);
}
