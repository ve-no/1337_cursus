#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_num + 4) % N
#define RIGHT (philosopher_num + 1) % N

int		state[N];
int		philosopher_num[N] = {0, 1, 2, 3, 4};

sem_t	mutex;
sem_t	S[N];

void	test(int philosopher_num)
{
	if (state[philosopher_num] == HUNGRY && state[LEFT] != EATING
		&& state[RIGHT] != EATING)
	{
		state[philosopher_num] = EATING;
		sleep(2);
		printf("Philosopher %d takes fork %d and %d\n",
				philosopher_num + 1,
				LEFT + 1,
				philosopher_num + 1);
		printf("Philosopher %d is Eating\n", philosopher_num + 1);
		sem_post(&S[philosopher_num]);
	}
}

void	take_forks(int philosopher_num)
{
	sem_wait(&mutex);
	state[philosopher_num] = HUNGRY;
	printf("Philosopher %d is hungry\n", philosopher_num + 1);
	test(philosopher_num);
	sem_post(&mutex);
	sem_wait(&S[philosopher_num]);
	sleep(1);
}

void	put_forks(int philosopher_num)
{
	sem_wait(&mutex);
	state[philosopher_num] = THINKING;
	printf("Philosopher %d is thinking\n", philosopher_num + 1);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}

void	*philosopher(void *num)
{
	int	*i;

	while (1)
	{
		i = num;
		sleep(1);
		take_forks(*i);
		sleep(0);
		put_forks(*i);
	}
}

int	main(void)
{
	int			i;
	pthread_t	thread_id[N];

	sem_init(&mutex, 0, 1);
	for (i = 0; i < N; i++)
		sem_init(&S[i], 0, 0);
	for (i = 0; i < N; i++)
	{
		pthread_create(&thread_id[i], NULL, philosopher, &philosopher_num[i]);
		printf("Philosopher %d is thinking\n", i + 1);
	}
	for (i = 0; i < N; i++)
		pthread_join(thread_id[i], NULL);
}
