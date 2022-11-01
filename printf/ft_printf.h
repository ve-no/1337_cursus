/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:15:38 by ael-bako          #+#    #+#             */
/*   Updated: 2022/10/28 16:15:32 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

char	*ft_itoa(int n);
int		ft_printunsigned(unsigned int n);
int		ft_printf(const char *format, ...);
int		ft_printhex(unsigned int num, const char format);
int		ft_printptr(unsigned long long ptr);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *str);
int		ft_printstr(char *str);
int		ft_printnbr(int n);
int		ft_printchar(int c);

#endif
