/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:59:16 by ael-bako          #+#    #+#             */
/*   Updated: 2022/11/08 20:18:55 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int ac, char **av)
{
	char *str;
	str = av[1];
	int i = 0 , j = 0;
	if (ac == 2)
	{
		while (str[i])
		{
			j = 0;
			if ((str[i] >= 'a' && str[i] <= 'z'))
			for (j = 0; j <= str[i] - 'a'; j++ )
				write(1, &str[i], 1);
			else if ((str[i] >= 'A' && str[i] <= 'Z'))
				while (j <= str[i] - 'A')
				{
					write(1, &str[i], 1);
					j++;
				}
			else
				write(1, &str[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
