/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:20:13 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/20 19:41:06 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
		ft_memcpy (dst, src, len);
	else
	{
		s1 = (unsigned char *)(dst + (len - 1));
		s2 = (unsigned char *)(src + (len - 1));
		while (len--)
			*s1-- = *s2--;
	}
	return (dst);
}
