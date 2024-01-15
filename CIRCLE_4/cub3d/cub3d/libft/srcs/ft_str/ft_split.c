/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:40:38 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/23 09:05:04 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_w(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i] == c)
		i++;
	if (i < len)
		j++;
	while (s[i] && i < len)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
		{
			j++;
			i++;
		}
		i++;
	}
	return (j);
}

static char	*w_dup(char const *s, int start, int fin)
{
	int		i;
	char	*str;

	str = malloc((fin - start) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < fin)
	{
		str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_error(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	**make_s(const char *s, char **ptr, char c, int start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && start >= 0)
		{
			ptr[j++] = w_dup(s, start, i);
			if (!ptr[j - 1])
				return (ft_error(ptr));
			start = -1;
		}
		i++;
	}
	ptr[j] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		start;

	start = -1;
	if (!s)
		return (NULL);
	ptr = malloc((count_w(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr = make_s(s, ptr, c, start);
	return (ptr);
}
