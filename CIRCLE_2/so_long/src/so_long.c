/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:23:37 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/16 14:49:14 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_sprite(t_program *ap)
{
	ap->p_down = mlx_xpm_file_to_image(ap->mlx, "./textures/p_down.xpm",
			&ap->i_size, &ap->i_size);
	ap->player = ap->p_down;
	ap->p_up = mlx_xpm_file_to_image(ap->mlx, "./textures/p_up.xpm",
			&ap->i_size, &ap->i_size);
	ap->p_right = mlx_xpm_file_to_image(ap->mlx, "./textures/p_right.xpm",
			&ap->i_size, &ap->i_size);
	ap->p_left = mlx_xpm_file_to_image(ap->mlx, "./textures/p_left.xpm",
			&ap->i_size, &ap->i_size);
	ap->sand = mlx_xpm_file_to_image(ap->mlx, "./textures/sand.xpm",
			&ap->i_size, &ap->i_size);
	ap->wall = mlx_xpm_file_to_image(ap->mlx, "./textures/wall.xpm",
			&ap->i_size, &ap->i_size);
	ap->coins = mlx_xpm_file_to_image(ap->mlx, "./textures/coins.xpm",
			&ap->i_size, &ap->i_size);
	ap->lock = mlx_xpm_file_to_image(ap->mlx, "./textures/lock.xpm",
			&ap->i_size, &ap->i_size);
	ap->unlock = mlx_xpm_file_to_image(ap->mlx, "./textures/unlock.xpm",
			&ap->i_size, &ap->i_size);
	if (!ap->sand || !ap->p_down || !ap->p_up || !ap->p_right
		|| !ap->p_left || !ap->wall || !ap->coins || !ap->lock || !ap->unlock)
	{
		write_err(4, NULL);
		exit_program(ap);
	}
}

int	key_hook_a(int keycode, t_program *ap)
{
	if (keycode == ESC)
		exit_program(ap);
	if (keycode == DOWN1 || keycode == DOWN2)
		ap->player = ap->p_down;
	else if (keycode == UP1 || keycode == UP2)
		ap->player = ap->p_up;
	else if (keycode == RIGHT1 || keycode == RIGHT2)
		ap->player = ap->p_right;
	else if (keycode == LEFT1 || keycode == LEFT2)
		ap->player = ap->p_left;
	if (keycode == UP1 || keycode == UP2
		|| keycode == RIGHT1 || keycode == RIGHT2
		|| keycode == DOWN1 || keycode == DOWN2
		|| keycode == LEFT1 || keycode == LEFT2)
		moving(keycode, ap);
	return (0);
}

void	moving(int key, t_program *ap)
{
	static int	moving;

	ap->render = 0;
	ap->data->y = ap->data->p_y + (key == DOWN1) + (key == DOWN2)
		- (key == UP1) - (key == UP2);
	ap->data->x = ap->data->p_x + (key == RIGHT1) + (key == RIGHT2)
		- (key == LEFT1) - (key == LEFT2);
	if (ft_strchr("C0", ap->data->map[ap->data->y][ap->data->x]))
		ap->render = 1;
	if (ap->data->map[ap->data->y][ap->data->x] == 'C')
		ap->data->check->coins--;
	if (ap->data->map[ap->data->y][ap->data->x] == 'E'
		&& ap->data->check->coins == 0)
		rip_program(ap);
	if (ap->render)
	{
		if (ap->data->check->coins == 0)
			ap->lock = ap->unlock;
		ap->data->map[ap->data->p_y][ap->data->p_x] = '0';
		ap->data->map[ap->data->y][ap->data->x] = 'P';
		ap->data->p_y = ap->data->y;
		ap->data->p_x = ap->data->x;
		showing_img(ap);
		ft_printf("move : %d\n", ++moving);
	}
}

int	showing_img(t_program *ap)
{
	ap->data->y = -1;
	while (ap->data->map[++ap->data->y])
	{
		ap->data->x = -1;
		while (ap->data->map[ap->data->y][++ap->data->x])
		{
			if (ap->data->map[ap->data->y][ap->data->x] == '1')
				mlx_put_image_to_window(ap->mlx, ap->window, ap->wall,
					ap->data->x * 60, ap->data->y * 60);
			if (ap->data->map[ap->data->y][ap->data->x] == '0')
				mlx_put_image_to_window(ap->mlx, ap->window, ap->sand,
					ap->data->x * 60, ap->data->y * 60);
			if (ap->data->map[ap->data->y][ap->data->x] == 'C')
				mlx_put_image_to_window(ap->mlx, ap->window, ap->coins,
					ap->data->x * 60, ap->data->y * 60);
			if (ap->data->map[ap->data->y][ap->data->x] == 'P')
				mlx_put_image_to_window(ap->mlx, ap->window, ap->player,
					ap->data->x * 60, ap->data->y * 60);
			if (ap->data->map[ap->data->y][ap->data->x] == 'E')
				mlx_put_image_to_window(ap->mlx, ap->window, ap->lock,
					ap->data->x * 60, ap->data->y * 60);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_program	*ap;

	if (ac != 2)
		return (write_err(0, NULL));
	ap = ft_calloc(1, sizeof(t_program));
	if (!ap)
		return (write(2, "Error\n Couldn't allocate for program\n", 37));
	ap->data = ft_calloc(1, sizeof(t_data));
	if (!ap->data)
		return (write(2, "Error\n Couldn't allocate for data\n", 34));
	if (!map(ap->data, av[1]))
	{
		free_memory(&ap);
		return (0);
	}
	ap->mlx = mlx_init();
	if (!ap->mlx)
		return (write(2, "Error\n Couldn't allocate for mlx_init", 38));
	new_window(ap);
	ft_sprite(ap);
	write(1, GREEN "[ so_long launch successfully ]\n" WHT, 46);
	showing_img(ap);
	mlx_hook(ap->window, 2, 0, key_hook_a, ap);
	mlx_loop(ap->mlx);
	return (0);
}
