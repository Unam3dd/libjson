#include "libjson.h"
#include <stdlib.h>
#include <assert.h>

int main(int ac, char **av)
{
	if (ac != 2) return (1);

	json_parse_t	parser = { NULL, { NULL, NULL, 0 }, 0 };
	json_file_t		f = { NULL, 0, 0 };

	if (json_read_file(&f, av[1]) == JSON_ERR)
		return (1);

	json_parse(&parser, &f);

	free((void *)f.buf);

	return (0);
}
