/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:36:00 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/14 17:41:26 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_program(t_program *ap)
{
	mlx_destroy_window(ap->mlx, ap->window);
	free_tab(ap->data->map);
	free(ap->data);
	free(ap);
	exit(0);
	return (0);
}

void	rip_program(t_program *ap)
{
	write(1, GREEN "\n\n\t|- - - WOOOW HHH !! - - -|\n\n", 37);
	exit_program(ap);
}

void	free_memory(t_program **ap)
{
	if ((*ap)->data->c_map)
		free_tab((*ap)->data->c_map);
	if ((*ap)->data->map)
		free_tab((*ap)->data->map);
	if ((*ap)->data->fd > 0)
		close((*ap)->data->fd);
	free((*ap)->data);
	free((*ap));
}

int	ft_close(t_program *ap)
{
	exit_program(ap);
	return (0);
}

void	new_window(t_program *ap)
{
	ap->window = mlx_new_window(ap->mlx, 60 * ap->data->width,
			60 * ap->data->height, "./so_long");
	if (!ap->window)
	{
		write(2, "Error\n Couldn't allocate for X window.", 37);
		exit_program(ap);
	}

	mlx_hook(ap->window, 17, 0, ft_close, ap);
}