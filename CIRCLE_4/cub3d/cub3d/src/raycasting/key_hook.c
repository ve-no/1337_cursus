/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:53:43 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/25 13:13:54 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_has_wall_at(float x, float y, t_cub *cub)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || y < 0 || (y >= (cub->mx->height * TILE_SIZE)))
		return (1);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (map_grid_index_x >= ft_strlen(cub->mx->map2[map_grid_index_y]))
		return (1);
	return (cub->mx->map2[map_grid_index_y][map_grid_index_x] == '1');
}

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	else if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->vertical = +1;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->vertical = -1;
	else if (keycode == D_KEY)
		cub->player->horizontal = +1;
	else if (keycode == A_KEY)
		cub->player->horizontal = -1;
	else if (keycode == RIGHT_KEY)
		cub->player->turndir = +1;
	else if (keycode == LEFT_KEY)
		cub->player->turndir = -1;
	return (0);
}

int	set_defeult(int keycode, t_cub *cub)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->vertical = 0;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->vertical = 0;
	else if (keycode == D_KEY)
		cub->player->horizontal = 0;
	else if (keycode == A_KEY)
		cub->player->horizontal = 0;
	else if (keycode == RIGHT_KEY)
		cub->player->turndir = 0;
	else if (keycode == LEFT_KEY)
		cub->player->turndir = 0;
	return (0);
}
