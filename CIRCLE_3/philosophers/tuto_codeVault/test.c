


// void	ft_usleep(int ms)
// {
// 	long int	time;

// 	time = ft_times();
// 	while (ft_times() - time < ms)
// 		usleep(ms / 10);
// }

// void	ft_print(t_philo *philo, char *str)
// {
// 	long int	time;

// 	pthread_mutex_lock(&(philo->info->print));
// 	time = ft_times() - philo->info->t_start;
// 	if (!philo->info->stop && time >= 0
// 		&& time <= INT_MAX && !ft_is_dead(philo, 0))
// 		printf("%lld ms\t philo_%d \t %s", ft_times() - philo->info->t_start,
// 			philo->n, str);
// 	pthread_mutex_unlock(&(philo->info->print));
// }

// void	ft_freeall(t_info *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->n_philo)
// 	{
// 		pthread_mutex_destroy(&data->philo[i].fork_l);
// 		pthread_mutex_destroy(data->philo[i].fork_r);
// 	}
// 	free(data->philo);
// 	pthread_mutex_destroy(&data->print);
// 	pthread_mutex_destroy(&data->m_stop);
// 	pthread_mutex_destroy(&data->m_eat);
// 	pthread_mutex_destroy(&data->dead);
// }

// int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	res;
// 	int	signe;

// 	i = 0;
// 	signe = 1;
// 	res = 0;
// 	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
// 		i++;
// 	if (str[i] == '-')
// 	{
// 		signe *= -1;
// 		i++;
// 	}
// 	else if (str[i] == '+')
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		res = res * 10 + str[i] - '0';
// 		i++;
// 	}
// 	return (res * signe);
// }

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdio.h>

// long long	ft_times(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// int main() {
//     srand(time(NULL));  // seed the random number generator
//     int duration = rand() % 500000 + 500000;  // generate a random duration between 0.5 and 1 second
//     printf("Pausing for 0.%d seconds...\n", duration / 100000);
//     usleep(duration);
//     printf("Done. %lld\n", ft_times());
//     return 0;
// }
// char *no_space(const char *str_in)
// {
//     int i = -1, j = 0;
//     char *str;
//     str = malloc(strlen(str_in));
//     while (str_in[++i])
//         if(str_in[i] != ' ')
//             str[j++] = str_in[i];
//     str[j] = '\0';
//     return str;
// }

// char *repeat_str(size_t count, const char *src)
// {
//     char *str;
//     int i , j = 0;
//     str = malloc(strlen(src) * count + 1);

//     while (count)
//     {
//         i = -1;
//         while(src[++i])
//             str[j++] = src[i];
//         count--;
//     }
//     str[j] = '\0';

//   return str;
// }
// int	ft_check_num(char **av)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (av[++i])
// 	{
// 		j = -1;
// 		while (av[i][++j])
// 		{
// 			if (av[i][j] < '0' || av[i][j] > '9')
// 				return (1);
// 		}
// 	}
// 	return (0);
// }
#include <stdbool.h>

// bool valid_parentheses(const char* str) {
//   int res = 0, i = -1, len = strlen(str);
//   while (++i < len && res >= 0)
//     res += (str[i] == '(') ? 1 : -1;
//     return (res == 0);
// }
// unsigned get_number (void)
// {
//   static int i = 0;
//   if (i == 0)
//     return ++i;
//   i *= 2;
//   return i;
// }

// size_t get_count(const char *s)
// {
//   int len = 0;
//   while(*s)
//   {
//     if (*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u')
//       len++;
//     s++;
//   }
//     return len;
// }
int round_to_next5(int n)
{

}
int main(int ac, char **av)
{

   
    printf(":%zu:\n", get_count("abracadabra"));
}
