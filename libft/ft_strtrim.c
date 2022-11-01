/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:26:31 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/23 20:39:51 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	check_set(char const *set, int s)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*ptr;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	ptr = (char *)s1;
	len = (int)ft_strlen (s1) - 1;
	if (!s1)
		return (NULL);
	while (ptr[len] && check_set(set, ptr[len]))
		len--;
	if (len < 0)
		return (ft_strdup(""));
	while (ptr[i] && check_set(set, ptr[i]))
		i++;
	ptr = ft_substr(s1, i, len - i + 1);
	return (ptr);
}
