# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				n;
	int				m_count;
	bool			is_eating;
	pthread_t		thread;
	long int		last_eat;
	struct s_info	*info;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}		t_philo;

typedef struct s_info
{
	int				philo_eat;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				stop;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
}		t_info;

int	ft_is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->info->dead);
	if (nb)
		philo->info->stop = 1;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

long long	ft_times(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = ft_times();
	while (ft_times() - time < ms)
		usleep(ms / 10);
}

void	ft_print(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->info->print));
	time = ft_times() - philo->info->t_start;
	if (!philo->info->stop && time >= 0
		&& time <= INT_MAX && !ft_is_dead(philo, 0))
		printf("%lld ms\t philo_%d \t %s", ft_times() - philo->info->t_start,
			philo->n, str);
	pthread_mutex_unlock(&(philo->info->print));
}

// Destroy all fork mutexes
// Destroy all other mutexes
// Free memory for philo array
void	ft_freeall(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->dead);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	signe = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * signe);
}

void	*ft_check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->t_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (!ft_is_dead(philo, 0) && ft_times() - \
			philo->last_eat >= (long)(philo->info->t_die))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		ft_print(philo, " died\n");
		ft_is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}



void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	ft_print(philo, " has taken a fork\n");
	if (philo->info->n_philo == 1)
	{
		ft_usleep(philo->info->t_die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	ft_print(philo, " has taken a fork\n");
}

void	ft_philo_eat(t_philo *philo)
{
	ft_print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->last_eat = ft_times();
	philo->m_count++;
	pthread_mutex_unlock(&(philo->info->m_eat));
	ft_usleep(philo->info->t_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	ft_print(philo, " is sleeping\n");
	ft_usleep(philo->info->t_sleep);
	ft_print(philo, " is thinking\n");
}

void	*ft_philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	if (philo->n % 2 == 0)
		ft_usleep(philo->info->t_eat / 10);
	while (!ft_is_dead(philo, 0))
	{
		pthread_create(&t, NULL, ft_check_death, phi);
		ft_take_fork(philo);
		ft_philo_eat(philo);
		pthread_detach(t);
		if (philo->m_count == philo->info->n_eat)
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->n_philo)
			{
				pthread_mutex_unlock(&philo->info->m_stop);
				ft_is_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}

int	ft_philo_init(t_info *data)
{
	int	i;

	data->t_start = ft_times();
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].n = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].info = data;
		data->philo[i].m_count = 0;
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->n_philo - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
		if (pthread_create(&data->philo[i].thread, NULL, \
				&ft_philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->n_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	ft_init(t_info *data, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->philo_eat = 0;
	if (av[5])
		data->n_eat = ft_atoi(av[5]);
	if (av[5] && data->n_eat == 0)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (2);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	return (0);
}

int	ft_check_num(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info	data;

	if (ac != 5 && ac != 6)
		return (write (1, "Error: Number of arguments invalid\n", 35));
	if (ft_check_num(av))
		return (write (1, "Error: Arguments must be a positive numbers\n", 44));
	if (ft_init(&data, av))
		return (write (1, "Error\n", 6));
	ft_philo_init(&data);
	ft_freeall(&data);
}



// This is a program for a simulation of the dining philosopher problem, a classic synchronization problem in computer science. In this problem, there are five philosophers sitting at a round table, and there are five forks on the table that the philosophers can use to eat. Each philosopher has to pick up two forks (one on their left and one on their right) to be able to eat. Once they finish eating, they must put the forks back on the table and continue thinking or sleeping until they are hungry again. The problem is to prevent deadlocks and starvation, so that each philosopher can eat, without any of them waiting indefinitely for a fork or getting stuck without ever getting one.

// The program uses pthreads to create threads for each philosopher, which runs a function called ft_philo_life. Each philosopher is represented by a t_philo struct, which contains information such as the philosopher's number, whether they are currently eating, and the last time they ate. Another struct t_info is used to keep track of the simulation parameters, such as the number of philosophers, the time it takes to eat, and the time it takes to sleep.

// Here's an overview of the different functions in the program:

// ft_times: This function returns the current time in milliseconds, using the gettimeofday function from the sys/time.h library.

// ft_usleep: This function sleeps for a given number of milliseconds, using the usleep function from the unistd.h library. It uses the ft_times function to keep track of the time.

// ft_print: This function prints a message with a timestamp indicating the philosopher number and the action being performed. It uses a mutex to ensure that multiple threads don't try to print at the same time.

// ft_freeall: This function is used to free all the memory allocated for the simulation. It destroys all the mutexes and frees the memory for the t_philo and t_info structs.

// ft_atoi: This function converts a string to an integer, similar to the atoi function from the stdlib.h library.

// ft_check_death: This function is used to check if a philosopher has died due to starvation. It sleeps for the specified time it takes for a philosopher to die, and if the philosopher hasn't eaten during that time, it sets a flag to indicate that the simulation should stop and prints a message saying the philosopher has died.

// ft_is_dead: This function checks if the simulation should stop due to a philosopher dying or if it has already stopped.

// ft_take_fork: This function is used by a philosopher to pick up the forks. It first locks the mutex for the fork on its left, then prints a message indicating that it has taken that fork. If there is only one philosopher, it waits for twice the time it takes for a philosopher to die before returning. Otherwise, it locks the mutex for the fork on its right, prints a message indicating that it has taken that fork, and returns.

// ft_philo_eat: This function is used by a philosopher to eat. It prints a message indicating that it is eating, updates the last_eat time, increments the number of meals, sleeps for the specified time it takes for a philosopher to eat, and then releases the forks.

// ft_philo_life: This is the main function that runs for each philosopher thread. It first initializes the last_eat time, then enters an infinite loop. In each iteration of the loop, it first checks if the simulation should stop, and if so, it breaks out of the loop. It then calls ft_take_fork to pick up the forks, then calls `ft_philo_eat



// ft_times()
// This function returns the current time in milliseconds using the gettimeofday() function. It's used to calculate the elapsed time in the program.

// ft_usleep(int ms)
// This function takes a number of milliseconds as an argument and puts the calling thread to sleep for that amount of time. It's used to simulate the passage of time in the program.

// ft_print(t_philo *philo, char *str)
// This function takes a t_philo structure pointer and a string as arguments. It acquires the lock on the print mutex in the t_info structure, which ensures that only one thread can print at a time. It then calculates the time elapsed since the start of the program and prints a message containing the philosopher's number, the elapsed time, and the string argument. If the stop flag in the t_info structure is set or the philosopher has died, the message is not printed. The lock on the print mutex is released before the function returns.

// ft_freeall(t_info *data)
// This function takes a t_info structure pointer as an argument. It iterates through the t_philo array in the t_info structure and destroys the mutexes associated with each philosopher's left and right forks. It then frees the memory allocated for the t_philo array. Finally, it destroys the print, m_stop, m_eat, and dead mutexes in the t_info structure.

// ft_atoi(const char *str)
// This function takes a string containing a number as an argument and returns the integer value of that number. It ignores any leading whitespace characters and handles both positive and negative numbers.

// ft_check_death(void *phi)
// This function is the entry point for a philosopher's life thread. It takes a t_philo structure pointer as an argument. The thread is responsible for monitoring the philosopher's state and checking whether they have starved to death. The thread sleeps for t_die + 1 milliseconds and then acquires the locks on the m_eat and m_stop mutexes in the t_info structure. If the philosopher has not already died and has not





// ft_times(): This function gets the current time in milliseconds using the gettimeofday() function, and returns it as a long long integer.

// ft_usleep(int ms): This function causes the calling thread to sleep for a specified number of milliseconds using the usleep() function.

// ft_print(t_philo *philo, char *str): This function prints the current time in milliseconds, the philosopher's number, and a given string to the console. It does so by acquiring a lock on a mutex that protects the console output to prevent multiple threads from writing to it simultaneously.

// ft_freeall(t_info *data): This function destroys all mutexes and frees memory allocated to the philosopher array.

// ft_atoi(const char *str): This function converts a string to an integer using a similar approach to the standard library atoi() function.

// ft_check_death(void *phi): This function checks if a philosopher has died due to starvation. It does so by waiting for a specified amount of time (t_die) and checking if the philosopher has eaten within that time. If not, it signals that the philosopher has died.

// ft_is_dead(t_philo *philo, int nb): This function checks whether a philosopher is dead. If nb is non-zero, it sets a flag to indicate that the simulation has ended. It does this by acquiring a lock on a mutex that protects the shared stop variable.

// ft_take_fork(t_philo *philo): This function simulates a philosopher picking up a pair of forks. It does so by acquiring locks on the left and right forks, one at a time.

// ft_philo_eat(t_philo *philo): This function simulates a philosopher eating. It does so by acquiring a lock on a mutex that protects the shared m_eat variable, updating the philosopher's last_eat timestamp, releasing the forks, and waiting for a specified amount of time (t_eat).

// ft_philo_life(void *phi): This function is the main function for the philosopher threads. It simulates a philosopher's life cycle by repeatedly picking up forks, eating, sleeping, and thinking. It also periodically checks if the philosopher has died due to starvation.
