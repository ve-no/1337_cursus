# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

int	main(int ac, char **av, char** env)
{
		int		pipefd[2];
		int fdin = open ("test.js", O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(fdin, STDIN);
		write(0, "hello world ", 11);
		printf("%d\n", fdin);
	// printf("%d\n",execve("/bin/lsds", &av[1], env));
	// printf("hello");
}
