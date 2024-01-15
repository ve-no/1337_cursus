/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_race_condition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:04:24 by ael-bako          #+#    #+#             */
/*   Updated: 2023/03/28 00:02:08 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int		mails = 0;

void	*routine()
{
	for (int i = 0; i < 10000; i++)
	{
		mails++;
		// read mails
		// increment
		// write mails
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t p1, p2, p3, p4;
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(p1, NULL) != 0)
		return (3);
	if (pthread_join(p2, NULL) != 0)
		return (4);
	printf("Number of mails: %d\n", mails);
	return (0);
}
