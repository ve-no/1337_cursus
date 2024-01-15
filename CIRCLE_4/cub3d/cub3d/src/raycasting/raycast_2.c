/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:49:09 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/25 14:06:53 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	norm_find_ver(t_cub *cub, int found_vert_wall_hit)
{
	float	x_to_check;
	float	y_to_check;

	while ((cub->xintercept) >= 0
		&& (cub->xintercept) <= (cub->mx->width * TILE_SIZE)
		&& (cub->yintercept) >= 0
		&& (cub->yintercept) <= (cub->mx->height * TILE_SIZE))
	{
		x_to_check = (cub->xintercept) + is_facing(cub->is_ray_facing_left);
		y_to_check = (cub->yintercept);
		if (map_has_wall_at(x_to_check, y_to_check, cub))
		{
			cub->vertwallhit_x = (cub->xintercept);
			cub->vertwallhit_y = (cub->yintercept);
			found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			(cub->xintercept) += cub->xstep;
			(cub->yintercept) += cub->ystep;
		}
	}
	return (found_vert_wall_hit);
}

float	find_vertical_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	float	vert_hit_distance;

	if (norm_find_ver(cub, 0))
		vert_hit_distance = distance_between_points(cub->player->x,
				cub->player->y, cub->vertwallhit_x, cub->vertwallhit_y);
	else
		vert_hit_distance = INT_MAX;
	return (vert_hit_distance);
}

int	norm_find_hor(t_cub *cub, int found_horz_wall_hit)
{
	float	x_to_check;
	float	y_to_check;

	while ((cub->xintercept) >= 0
		&& (cub->xintercept) <= (cub->mx->width * TILE_SIZE)
		&& (cub->yintercept) >= 0
		&& (cub->yintercept) <= (cub->mx->height * TILE_SIZE))
	{
		x_to_check = (cub->xintercept);
		y_to_check = (cub->yintercept) + is_facing(cub->is_ray_facing_up);
		if (map_has_wall_at(x_to_check, y_to_check, cub))
		{
			cub->horzwallhit_x = (cub->xintercept);
			cub->horzwallhit_y = (cub->yintercept);
			found_horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			(cub->xintercept) += cub->xstep;
			(cub->yintercept) += cub->ystep;
		}
	}
	return (found_horz_wall_hit);
}

float	find_horizontal_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	float	hor_hit_distance;

	cub->horzwallhit_x = 0;
	cub->horzwallhit_y = 0;
	cub->horz_wall_content = 0;
	if (norm_find_hor(cub, 0))
		hor_hit_distance = distance_between_points(cub->player->x,
				cub->player->y, cub->horzwallhit_x, cub->horzwallhit_y);
	else
		hor_hit_distance = INT_MAX;
	return (hor_hit_distance);
}
