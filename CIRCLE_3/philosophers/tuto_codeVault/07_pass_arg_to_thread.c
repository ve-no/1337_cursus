#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void	*routine(void *arg)
{
	int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	int	index;

	sleep(1);
	index = *(int *)arg;
	printf("%d ", primes[index]);
	free(arg);
	return NULL;
}

int	main(int argc, char *argv[])
{
	pthread_t th[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to created thread");
	}
	for (i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
	}
	system("leaks a.out");
	return (0);
}
