/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_processes_vs_thread.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:24:07 by ael-bako          #+#    #+#             */
/*   Updated: 2023/03/28 00:00:11 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		x = 2;

void	*routine()
{
	x += 5;
	sleep(1);
	printf("Value of x: %d\n", x);
	return NULL;
}

void	*routine2()
{
	sleep(1);
	printf("Valuee of x: %d\n", x);
	return NULL;
}

int	main(int argc, char *argv[])
{
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine2, NULL))
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
	if (pthread_join(t2, NULL))
		return (3);
	return (0);
}
