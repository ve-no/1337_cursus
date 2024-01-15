/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:04:30 by ael-bako          #+#    #+#             */
/*   Updated: 2023/05/03 11:54:59 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_usable_size(void *ptr)
{
	size_t	*metadata;

	metadata = NULL;
	if (!ptr)
		return (0);
	*metadata = *((size_t *)ptr - 1);
	return (metadata[0]);
}

void	*ft_realloc(void *ptr, size_t size)
{
	size_t		old_size;
	size_t		copy_size;
	void		*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	old_size = ft_usable_size(ptr);
	if (old_size < size)
		copy_size = old_size;
	else
		copy_size = size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(new_ptr);
	return (realloc(ptr, size));
}
