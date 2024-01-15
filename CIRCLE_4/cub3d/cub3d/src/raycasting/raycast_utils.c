/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:50:53 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/23 09:05:04 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	*get_dir(t_cub *cub, int x)
{
	if (cub->ray[x]->was_hit_vertical && cub->ray[x]->is_facing_left)
		return (cub->sprit->we);
	else if (cub->ray[x]->was_hit_vertical && cub->ray[x]->is_facing_right)
		return (cub->sprit->ea);
	else if (!cub->ray[x]->was_hit_vertical && cub->ray[x]->is_facing_up)
		return (cub->sprit->no);
	return (cub->sprit->so);
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

void	calculate_ray_direction(float ray_angle, t_cub *cub)
{
	(cub->is_ray_facing_down) = (ray_angle > 0 && ray_angle < PI);
	(cub->is_ray_facing_up) = !((cub->is_ray_facing_down));
	(cub->is_ray_facing_right) = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	(cub->is_ray_facing_left) = !((cub->is_ray_facing_right));
}

void	render_ceiling(t_cub *cub, int y, int width, int height)
{
	int		i[2];

	i[0] = -1;
	while (++i[0] < width)
	{
		i[1] = -1;
		while (++i[1] < height)
		{
			my_mlx_pixel_put(cub->img, i[0], y + i[1],
				cub->mx->color2);
		}
	}
}

void	render_floor(t_cub *cub, int y, int width, int height)
{
	int		i[2];

	i[0] = -1;
	while (++i[0] < width)
	{
		i[1] = -1;
		while (++i[1] < height)
		{
			my_mlx_pixel_put(cub->img, i[0], y + i[1],
				cub->mx->color1);
		}
	}
}
