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

json_status_t	json_read_file(json_file_t *f, const char *filename)
{
	if (!f || !filename)
		return (JSON_ERR);

	int fd = open(filename, O_RDONLY);

	if (fd < 0)
		return (JSON_ERR);

	f->buf = NULL;
	f->pos = 0;
	f->size = (size_t)lseek(fd, 0, SEEK_END);
	
	lseek(fd, 0, SEEK_SET);

	f->buf = (const char *)calloc(sizeof(char), f->size + 1);

	if (!f->buf) {
		f->size = 0;
		close(fd);
		return (JSON_ERR);
	}

	if (read(fd, (void*)f->buf, f->size) != f->size) {
		free((void*)f->buf);
		f->buf = NULL;
		f->size = 0;
		close(fd);
		return (JSON_ERR);
	}

	close(fd);

	return (JSON_OK);
}
