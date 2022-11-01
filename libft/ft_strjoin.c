/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:45:53 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/07 18:18:11 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
