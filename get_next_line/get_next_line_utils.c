/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:47:49 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/31 18:04:36 by ael-bako         ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count && SIZE_MAX / size < count)
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
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
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2) +1;
	str = (char *)malloc(k);
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (i < ft_strlen(s1))
		str[k++] = s1[i++];
	i = 0;
	while (i < ft_strlen(s2))
		str[k++] = s2[i++];
	str[k] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s2[i] && s1[i] && i < n - 1)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (s_len - 1 < start || s_len == 0)
		return (ft_strdup(""));
	if (len > s_len - (size_t)start)
		len = s_len - (size_t)start;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (len > i && s[start] != '\0')
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
