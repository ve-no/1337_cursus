/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_pthread_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:09:14 by ael-bako          #+#    #+#             */
/*   Updated: 2023/03/28 00:04:07 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int				mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 1000000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment
		// write mails
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t p1, p2, p3, p4;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&p3, NULL, &routine, NULL) != 0)
		return (3);
	if (pthread_create(&p4, NULL, &routine, NULL) != 0)
		return (4);
	if (pthread_join(p1, NULL) != 0)
		return (5);
	if (pthread_join(p2, NULL) != 0)
		return (6);
	if (pthread_join(p3, NULL) != 0)
		return (7);
	if (pthread_join(p4, NULL) != 0)
		return (8);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
