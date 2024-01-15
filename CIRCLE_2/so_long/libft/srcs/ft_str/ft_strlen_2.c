/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:43:27 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/06 15:55:53 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: find length of two dimensional array
**
** DESCRIPTION:
** 		The strlen_2() function computes the length of the two dimensional
**		array s.
*/

#include "libft.h"

size_t	ft_strlen_2(char **s)
{
	size_t	len;

	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}
