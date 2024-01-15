/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:08:30 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/26 11:05:28 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	setup(t_cub *cub)
{
	move_player(cub);
	cast_all_rays(cub);
	generate_projection(cub, cub->ray);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win,
		cub->img->img, 0, 0);
	return (0);
}

t_img	*new_texture(void *mlx, char *path)
{
	t_img	*texture;

	texture = malloc(sizeof(t_img));
	if (!texture)
		ft_putstr_fd("Error in allocation \n", 2);
	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		ft_putstr_fd("Error in file xpm \n", 2);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (texture);
}

void	initialize(t_cub *cub, int i)
{
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	while (i < NUM_RAYS)
		cub->ray[i++] = malloc(sizeof(t_ray));
	if (!cub->data || !cub->player)
		ft_putstr_fd("Error in allocation \n", 2);
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		ft_putstr_fd("Error initializing mlx \n", 2);
	cub->data->win = mlx_new_window(cub->data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->data->win)
		ft_putstr_fd("Error creating mlx window \n", 2);
	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
		ft_putstr_fd("Error in allocation \n", 2);
	cub->img->img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	cub->sprit->no = new_texture(cub->data->mlx, cub->mx->no);
	cub->sprit->so = new_texture(cub->data->mlx, cub->mx->so);
	cub->sprit->we = new_texture(cub->data->mlx, cub->mx->we);
	cub->sprit->ea = new_texture(cub->data->mlx, cub->mx->ea);
}

float	get_ang(t_mx *mx)
{
	if (mx->p_dir == 'N')
		return (3 * M_PI_2);
	else if (mx->p_dir == 'S')
		return (M_PI_2);
	else if (mx->p_dir == 'E')
		return (0);
	return (M_PI);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	check_extension(ac, av[1]);
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->mx = malloc(sizeof(t_mx));
	parsing_map(cub->mx, av[1]);
	cub->mx->color1 = rgb_to_decimal(cub->mx->f);
	cub->mx->color2 = rgb_to_decimal(cub->mx->c);
	initialize(cub, -1);
	cub->player->x = (cub->mx->y * TILE_SIZE) + 32;
	cub->player->y = (cub->mx->x * TILE_SIZE) + 32;
	cub->player->angle = get_ang(cub->mx);
	cub->player->turndir = 0;
	cub->player->horizontal = 0;
	cub->player->vertical = 0;
	cub->player->turnspeed = 4 * (PI / 180);
	cub->player->walkspeed = 10;
	mlx_hook(cub->data->win, 2, 0, key_hook, cub);
	mlx_hook(cub->data->win, 3, 0, set_defeult, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	mlx_loop_hook(cub->data->mlx, setup, cub);
	mlx_loop(cub->data->mlx);
}
