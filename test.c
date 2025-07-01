#include <stdio.h>
#include "libjson.h"

int main(int ac, char **av)
{
	if (ac != 2) {
		fprintf(stderr, "usage: %s <filename>", av[0]);
		return (1);
	}

	lexer_t	l = { NULL, 0, 0 };

	if (json_read_file(&l, av[1])) {
		perror("read_file");
		return (1);
	}

	token_type_t	type = next_token(&l);

	while (type) {
		puts(get_string_token_type(type));
		type = next_token(&l);
	}

	return (0);
}
