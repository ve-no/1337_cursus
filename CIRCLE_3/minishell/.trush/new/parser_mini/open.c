#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *input;
	int fd;
	while (1)
	{
		if (fd > 2)
			close(fd);
		printf("%d", fd);
		input = readline("input: ");
		fd = open(input, 1);
		printf("%d\n",fd);
	}
}
