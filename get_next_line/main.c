#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int fd = open("open_close_open.txt", O_RDONLY);
	char *d = get_next_line(fd);
	while (d)
	{
		printf("%s", d);
		d = get_next_line(fd);
	}
	printf("%s", d);
}
