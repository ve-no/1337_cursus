/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:43:37 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/23 09:05:04 by ibouchaf         ###   ########.fr       */
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
