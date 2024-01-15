/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:43:37 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/24 12:16:06 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *s1, const	char *s2, size_t len)
{
	size_t	i;
	size_t	a;
	size_t	n_len;
	char	*str;

	i = 0;
	n_len = ft_strlen(s2);
	str = (char *)s1;
	if (n_len == 0 || s1 == s2)
		return (str);
	while (str[i] && i < len)
	{
		a = 0;
		while (str[a + i] && s2[a] && i + a < len
			&& str[a + i] == s2[a])
			a++;
		if (a == n_len)
			return (str + i);
		i++;
	}
	return (0);
}
