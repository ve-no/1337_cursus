/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_short_intro_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:00:03 by ael-bako          #+#    #+#             */
/*   Updated: 2023/02/02 14:10:08 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* routine()
{
	printf("Hello from threads\n");
	sleep(1);
	printf("Ending thread\n");
	return NULL;
}

int	main(int argc, char *argv[])
{
	pthread_t p1, p2;

	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(p1, NULL) != 0)
		return (3);
	if (pthread_join(p2, NULL) != 0)
		return (4);
	return (0);
}