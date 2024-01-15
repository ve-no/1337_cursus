/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:17:03 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/20 16:57:53 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(int n)
{
	int		count;
	long	res;

	res = n;
	count = 1;
	if (res < 0)
	{
		res *= -1;
		count++;
	}
	while (res >= 10)
	{
		res /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		i;
	long	res;

	i = 0;
	res = n;
	arr = malloc(size(n) + 1);
	if (!arr)
		return (NULL);
	if (n < 0)
	{
		arr[0] = '-';
		res *= -1;
	}
	arr[size(n) - i++] = '\0';
	while (res >= 10)
	{
		arr[size(n) - i++] = (res % 10) + '0';
		res /= 10;
	}
	arr[size(n) - i++] = (res % 10) + '0';
	return (arr);
}
