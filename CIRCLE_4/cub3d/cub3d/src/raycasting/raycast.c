/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:49:48 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/25 22:30:52 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	assign_hor_ver_ray(t_ray **rays, int stripId,
	float distance, t_cub *cub)
{
	if (stripId > 0)
	{
		rays[stripId]->distance = distance;
		rays[stripId]->wallhit_x = cub->vertwallhit_x;
		rays[stripId]->wallhit_y = cub->vertwallhit_y;
		rays[stripId]->wall_hit_content = cub->vert_wall_content;
		rays[stripId]->was_hit_vertical = TRUE;
	}
	else
	{
		stripId = stripId * -1;
		rays[stripId]->distance = distance;
		rays[stripId]->wallhit_x = cub->horzwallhit_x;
		rays[stripId]->wallhit_y = cub->horzwallhit_y;
		rays[stripId]->wall_hit_content = cub->horz_wall_content;
		rays[stripId]->was_hit_vertical = FALSE;
	}
}

void	cast_ray(float ray_angle, int stripId, t_ray **rays, t_cub *cub)
{
	float		horz_hit_distance;
	float		vert_hit_distance;

	ray_angle = normalize_angle(ray_angle);
	calculate_ray_direction(ray_angle, cub);
	calculate_horizontal_intersection(ray_angle, cub);
	horz_hit_distance = find_horizontal_wall_hit(rays, stripId, cub);
	calculate_vertical_intersection(ray_angle, cub);
	vert_hit_distance = find_vertical_wall_hit(rays, stripId, cub);
	if (vert_hit_distance < horz_hit_distance)
		assign_hor_ver_ray(rays, stripId, vert_hit_distance, cub);
	else
		assign_hor_ver_ray(rays, stripId * -1, horz_hit_distance, cub);
	rays[stripId]->ray_angle = ray_angle;
	rays[stripId]->is_facing_down = cub->is_ray_facing_down;
	rays[stripId]->is_facing_up = cub->is_ray_facing_up;
	rays[stripId]->is_facing_left = cub->is_ray_facing_left;
	rays[stripId]->is_facing_right = cub->is_ray_facing_right;
}

void	cast_all_rays(t_cub *cub)
{
	float	ray_angle;
	int		stripid;

	stripid = 0;
	ray_angle = cub->player->angle - (FOV_ANGLE / 2);
	while (stripid < NUM_RAYS)
	{
		cast_ray(ray_angle, stripid, cub->ray, cub);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		stripid++;
	}
}

void	ft_rect(t_cub *cub, int x, int y, int height)
{
	int				i;
	int				tex[2];
	float			scale[2];
	unsigned int	color;

	cub->texture = get_dir(cub, x);
	scale[0] = cub->texture->width / TILE_SIZE;
	tex[0] = cub->ray[x]->wallhit_x;
	if (cub->ray[x]->was_hit_vertical)
		tex[0] = cub->ray[x]->wallhit_y;
	tex[0] = fmod(((float)tex[0] * scale[0]), cub->texture->width);
	scale[1] = ((double)cub->texture->height / height);
	i = -1;
	while (++i < height)
	{
		tex[1] = (float) i * scale[1];
		my_mlx_pixel_put(cub->img, x, y + i,
			get_pixel_from_image(cub->texture, tex[0], tex[1]));
	}
}

void	generate_projection(t_cub *cub, t_ray **rays)
{
	int		i;
	float	perp_distance;
	float	dis_proj_lane;
	float	projected_wall_height;
	int		wall_top_pixel;

	i = 0;
	render_ceiling(cub, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	render_floor(cub, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
	while (i < NUM_RAYS)
	{
		perp_distance = rays[i]->distance * cos(rays[i]->ray_angle
				- cub->player->angle);
		dis_proj_lane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / perp_distance) * dis_proj_lane;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - ((int)projected_wall_height / 2);
		ft_rect(cub, i * WALL_STRIP_WIDTH, wall_top_pixel,
			(int)projected_wall_height);
		i++;
	}
}
