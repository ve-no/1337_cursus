/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:17:51 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/31 14:14:34 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)b;
	while (len)
	{
		*str = c;
		str++;
		len--;
	}
	return (b);
}

int main()
{
	int p[]={1,2,3,4};
	memset(p,5,4);
	int i = 0;
	while ( i< 4)
	{
		printf("%d\t",p[i]);
		i++;
	}
}
