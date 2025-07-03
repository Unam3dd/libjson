#include <stdio.h>
#include "libjson.h"
#include <stdlib.h>
#include <assert.h>

int main(int ac, char **av)
{
	if (ac != 2) {
		printf("usage: %s <filename>\n", av[0]);
		return (1);
	}

	json_file_t	f;

	assert(json_read_file(&f, av[1]) == JSON_OK);

	token_type_t	t = next_token(&f);


	while (t != TOKEN_STRING) {
		puts(get_string_token_type(t));
		t = next_token(&f);
	}

	free((void *)f.buf);
	f.pos = 0;
	f.size = 0;

	return (0);
}
