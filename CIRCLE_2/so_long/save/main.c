/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:06:15 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/17 11:09:36 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// void	random_images(t_program *ap, int x, int y)
// {
// 	static int	i;

// 	if (++i == 0)
// 		mlx_put_image_to_window(ap->mlx, ap->window, ap->enemy_0, y * 60, x
// 			* 60);
// 	else if (i == 1)
// 		mlx_put_image_to_window(ap->mlx, ap->window, ap->enemy_1, y * 60, x
// 			* 60);
// 	else if (i == 2)
// 		mlx_put_image_to_window(ap->mlx, ap->window, ap->enemy_2, y * 60, x
// 			* 60);
// 	else if (i == 3)
// 		mlx_put_image_to_window(ap->mlx, ap->window, ap->enemy_3, y * 60, x
// 			* 60);
// 	else if (i == 4)
// 		mlx_put_image_to_window(ap->mlx, ap->window, ap->enemy_4, y * 60, x
// 			* 60);
// 	else if (i == 5)
// 		mlx_put_image_to_window(ap->mlx, ap->window, ap->enemy_5, y * 60, x
// 			* 60);
// 	else if (i == 6)
// 		mlx_put_image_to_window(ap->mlx, ap->window, ap->enemy_6, y * 60, x
// 			* 60);
// 	else if (i == 8)
// 		i = -1;
// }

// int	ft_animation(t_program *ap)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (ap->data->map[++y])
// 	{
// 		x = -1;
// 		while (ap->data->map[y][++x])
// 		{
// 			if (ap->data->map[y][x] == 'Z')
// 				random_images(ap, y, x);
// 		}
// 	}
// 	return (1);
// }

void	ft_mlx_string_put(t_program *ap, int mv)
{
	ap->data->line = ft_itoa(mv);
	mlx_string_put(ap->mlx, ap->window, (ap->data->width / 2) * 60, 20,
		INT_MAX, ft_strcat(ap->data->line, " : move"));
	free(ap->data->line);
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
	showing_img(ap);
	mlx_hook(ap->window, 2, 0, key_hook_a, ap);
	// mlx_loop_hook(ap->mlx, ft_animation, ap);
	mlx_loop(ap->mlx);
	return (0);
}
