/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 08:24:57 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/23 09:05:04 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*handle_string_argument(char *current,
		size_t *remaining_size, va_list args)
{
	const char	*str_arg;
	size_t		str_len;

	str_arg = va_arg(args, const char *);
	str_len = ft_strlen(str_arg);
	if (str_len < *remaining_size)
	{
		ft_strncpy(current, str_arg, *remaining_size);
		current += str_len;
		*remaining_size -= str_len;
	}
	else
	{
		ft_strncpy(current, str_arg, *remaining_size - 1);
		current += *remaining_size - 1;
		*remaining_size = 0;
	}
	return (current);
}

int	my_snprintf(char *str, size_t size, const char *format, ...)
{
	char		*current;
	size_t		remaining_size;
	va_list		args;

	va_start(args, format);
	current = str;
	remaining_size = size;
	while (*format && current < (str + size - 1))
	{
		if (*format == '%' && *(format + 1) == 's')
		{
			current = handle_string_argument(current, &remaining_size, args);
			format += 2;
		}
		else
		{
			*current++ = *format++;
			remaining_size--;
			if (remaining_size == 0)
				break ;
		}
	}
	va_end(args);
	*current = '\0';
	return (current - str);
}
