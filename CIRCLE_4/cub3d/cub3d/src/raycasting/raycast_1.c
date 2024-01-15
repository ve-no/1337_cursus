/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:46:42 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/26 11:00:56 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	get_pixel_from_image(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x
			* (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	calculate_horizontal_intersection(float rayAngle, t_cub *cub)
{
	cub->yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (cub->is_ray_facing_down)
		cub->yintercept += TILE_SIZE;
	cub->xintercept = cub->player->x
		+ (cub->yintercept - cub->player->y) / tan(rayAngle);
	cub->ystep = TILE_SIZE;
	if (cub->is_ray_facing_up)
		cub->ystep *= -1;
	cub->xstep = TILE_SIZE / tan(rayAngle);
	if ((cub->is_ray_facing_left && (cub->xstep > 0)))
		cub->xstep *= -1;
	if ((cub->is_ray_facing_right && (cub->xstep < 0)))
		cub->xstep *= -1;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || y >= WINDOW_HEIGHT
		|| x >= WINDOW_WIDTH)
		return ;
	dst = img->addr + (y * img->line_length + x
			* (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	move_player(t_cub *cub)
{
	float	move_step_ver;
	float	move_step_hor;
	float	xstep;
	float	ystep;

	xstep = 0;
	ystep = 0;
	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	move_step_ver = cub->player->vertical * cub->player->walkspeed;
	move_step_hor = cub->player->horizontal * cub->player->walkspeed;
	xstep += (cos(cub->player->angle) * move_step_ver);
	xstep += (cos(cub->player->angle + PI / 2) * move_step_hor);
	ystep += (sin(cub->player->angle + PI / 2) * move_step_hor);
	ystep += (sin(cub->player->angle) * move_step_ver);
	xstep *= 5;
	ystep *= 5;
	if (!map_has_wall_at(cub->player->x + xstep, cub->player->y, cub))
		cub->player->x += xstep / 5;
	if (!map_has_wall_at(cub->player->x, cub->player->y + ystep, cub))
		cub->player->y += ystep / 5;
}

void	calculate_vertical_intersection(float rayAngle, t_cub *cub)
{
	cub->xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (cub->is_ray_facing_right)
		cub->xintercept += TILE_SIZE;
	cub->yintercept = cub->player->y
		+ (cub->xintercept - cub->player->x) * tan(rayAngle);
	cub->xstep = TILE_SIZE;
	if (cub->is_ray_facing_left)
		cub->xstep *= -1;
	cub->ystep = TILE_SIZE * tan(rayAngle);
	if (cub->is_ray_facing_up && (cub->ystep > 0))
		cub->ystep *= -1;
	if (cub->is_ray_facing_down && (cub->ystep < 0))
		cub->ystep *= -1;
}
