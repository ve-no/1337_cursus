/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:47:49 by ael-bako          #+#    #+#             */
/*   Updated: 2022/11/01 12:02:28 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup(char *s1)
{
	size_t	size;
	size_t	i;
	char	*str;

	size = ft_strlen(s1) + 1;
	i = 0;
	str = (char *)malloc(size);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*p;
// 	size_t	i;
// 	size_t	s_len;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	i = 0;
// 	if (s_len - 1 < start || s_len == 0)
// 		return (ft_strdup(""));
// 	if (len > s_len - (size_t)start)
// 		len = s_len - (size_t)start;
// 	p = malloc(len + 1);
// 	if (!p)
// 		return (NULL);
// 	while (len > i && s[start] != '\0')
// 		p[i++] = s[start++];
// 	p[i] = '\0';
// 	return (p);
// }
