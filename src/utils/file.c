#include "libjson.h"

///////////////////////////////////////
//
//           INCLUDES
//
//////////////////////////////////////

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

///////////////////////////////////////
//
//            FILE
//
//////////////////////////////////////

int	json_read_file(lexer_t *l, const char *filename)
{
	if (!l || !filename)
		return (1);

	int fd = open(filename, O_RDONLY);

	if (fd < 0)
		return (1);

	l->buf = NULL;
	l->pos = 0;
	l->size = (size_t)lseek(fd, 0, SEEK_END);
	
	lseek(fd, 0, SEEK_SET);

	l->buf = (const char *)calloc(sizeof(char), l->size + 1);

	if (!l->buf) {
		l->size = 0;
		close(fd);
		return (1);
	}

	if (read(fd, (void*)l->buf, l->size) != l->size) {
		free((void*)l->buf);
		l->buf = NULL;
		l->size = 0;
		close(fd);
		return (1);
	}

	close(fd);

	return (0);
}
