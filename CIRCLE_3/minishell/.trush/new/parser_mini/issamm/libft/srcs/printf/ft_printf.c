/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:08:21 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/06 16:16:30 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_specifier(va_list args, const char format)
{
	int	print_count;

	print_count = 0;
	if (format == 'c')
		print_count += ft_printchar((char)va_arg(args, int));
	else if (format == 's')
		print_count += ft_printstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		print_count += ft_printnbr(va_arg(args, int));
	else if (format == 'x')
		print_count += ft_printhex(va_arg(args, int), 'x');
	else if (format == 'X')
		print_count += ft_printhex(va_arg(args, int), 'X');
	else if (format == 'u')
		print_count += ft_printunsigned(va_arg(args, unsigned int));
	else if (format == '%')
		print_count += ft_printchar('%');
	else if (format == 'p')
		print_count += ft_printptr(va_arg(args, unsigned long long));
	return (print_count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		print_count;
	int		state;

	state = 0;
	print_count = 0;
	va_start(args, format);
	while (*format)
	{
		if (state == 0)
		{
			if (*format == '%')
				state = 1;
			else
				print_count += ft_printchar(*format);
		}
		else
		{
			print_count += ft_specifier(args, *format);
			state = 0;
		}
		format++;
	}
	va_end(args);
	return (print_count);
}
