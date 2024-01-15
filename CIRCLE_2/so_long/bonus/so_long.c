/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:23:37 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/17 11:49:09 by ael-bako         ###   ########.fr       */
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
void	ft_sprite_b(t_program *ap)
{
	ap->enemy_0 = mlx_xpm_file_to_image(ap->mlx, "./anim/enemy_0.xpm",
			&ap->i_size, &ap->i_size);
	ap->enemy_1 = mlx_xpm_file_to_image(ap->mlx, "./anim/enemy_1.xpm",
			&ap->i_size, &ap->i_size);
	ap->enemy_2 = mlx_xpm_file_to_image(ap->mlx, "./anim/enemy_2.xpm",
			&ap->i_size, &ap->i_size);
	ap->enemy_3 = mlx_xpm_file_to_image(ap->mlx, "./anim/enemy_3.xpm",
			&ap->i_size, &ap->i_size);
	ap->enemy_4 = mlx_xpm_file_to_image(ap->mlx, "./anim/enemy_4.xpm",
			&ap->i_size, &ap->i_size);
	ap->enemy_5 = mlx_xpm_file_to_image(ap->mlx, "./anim/enemy_5.xpm",
			&ap->i_size, &ap->i_size);
	ap->enemy_6 = mlx_xpm_file_to_image(ap->mlx, "./anim/enemy_6.xpm",
			&ap->i_size, &ap->i_size);
	if (!ap->enemy_0 || !ap->enemy_1 || !ap->enemy_2 || !ap->enemy_3
		|| !ap->enemy_4 || !ap->enemy_5 || !ap->enemy_6)
	{
		write_err(4, NULL);
		exit_program(ap);
	}
}

int	key_hook_a(int keycode, t_program *ap)
{
	if (keycode == ESC)
		exit_program(ap);
	if (keycode == DOWN1)
		ap->player = ap->p_down;
	else if (keycode == UP1)
		ap->player = ap->p_up;
	else if (keycode == RIGHT1)
		ap->player = ap->p_right;
	else if (keycode == LEFT1)
		ap->player = ap->p_left;
	if (keycode == UP1 || keycode == RIGHT1
		|| keycode == DOWN1 || keycode == LEFT1)
		moving(keycode, ap);
	return (0);
}

void	moving(int key, t_program *ap)
{
	static int	moving;

	ap->render = 0;
	ap->data->y = ap->data->p_y + (key == DOWN1) - (key == UP1);
	ap->data->x = ap->data->p_x + (key == RIGHT1) - (key == LEFT1);
	if (ft_strchr("C0", ap->data->map[ap->data->y][ap->data->x]))
		ap->render = 1;
	if (ap->data->map[ap->data->y][ap->data->x] == 'C')
		ap->data->check->coins--;
	if (ap->data->map[ap->data->y][ap->data->x] == 'E'
		&& ap->data->check->coins == 0)
		rip_program(ap);
	if (ap->data->map[ap->data->y][ap->data->x] == 'Z')
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
		ft_mlx_string_put(ap, ++moving);
	}
}

int	showing_img(t_program *ap)
{
	// move_enemy(ap);
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