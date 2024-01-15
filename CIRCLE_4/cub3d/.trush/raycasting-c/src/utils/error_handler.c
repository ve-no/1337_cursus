/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:15:25 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/04 15:15:28 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_str(char *str)
{
	ft_putstr_fd("cub3D: ", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	exit_error(char *str, char *err)
{
	ft_putstr_fd("cub3D: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	exit_strerr(char *str, int err)
{
	ft_putstr_fd("cub3D: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
	exit(EXIT_FAILURE);
}

void	exit_success(char *str)
{
	ft_putendl_fd(str, 1);
	exit(EXIT_SUCCESS);
}
