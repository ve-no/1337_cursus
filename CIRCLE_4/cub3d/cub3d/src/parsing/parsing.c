/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:27:39 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/25 14:46:13 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_identifier(t_mx *mlx, int i)
{
	if (ft_strncmp(mlx->map[i], "NO ", 3) == 0)
		return (mlx->no = ft_strtrim((
					ft_strchr(mlx->map[i], 'N') + 2), " \n\t"), 1);
	else if (ft_strncmp(mlx->map[i], "SO ", 3) == 0)
		return (mlx->so = ft_strtrim((
					ft_strchr(mlx->map[i], 'S') + 2), " \n\t"), 1);
	else if (ft_strncmp(mlx->map[i], "WE ", 3) == 0)
		return (mlx->we = ft_strtrim((
					ft_strchr(mlx->map[i], 'W') + 2), " \n\t"), 1);
	else if (ft_strncmp(mlx->map[i], "EA ", 3) == 0)
		return (mlx->ea = ft_strtrim((
					ft_strchr(mlx->map[i], 'E') + 2), " \n\t"), 1);
	else if (ft_strncmp(mlx->map[i], "F ", 2) == 0)
		return ((mlx->f = ft_strchr(mlx->map[i], 'F') + 1), 1);
	else if (ft_strncmp(mlx->map[i], "C ", 2) == 0)
		return ((mlx->c = ft_strchr(mlx->map[i], 'C') + 1), 1);
	return (0);
}

void	count_height(t_mx **mlx, int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		(*mlx)->height++;
	}
}

void	init(t_mx *mlx)
{
	mlx->map2 = NULL;
	mlx->no = NULL;
	mlx->so = NULL;
	mlx->we = NULL;
	mlx->ea = NULL;
	mlx->f = NULL;
	mlx->c = NULL;
	mlx->height = 0;
	mlx->width = 0;
	mlx->count = 0;
	mlx->map = NULL;
}

void	parsing_map(t_mx *mlx, char *av)
{
	int		i[3];
	char	**str;

	i[1] = 0;
	init(mlx);
	i[0] = open(av, O_RDONLY);
	if (i[0] < 0)
		ft_putstr_fd("no such file or directory \n", 2);
	count_height(&mlx, i[0]);
	mlx->map = malloc(sizeof(char *) * (mlx->height + 1));
	i[0] = open(av, O_RDONLY);
	while (mlx->height > i[1])
		mlx->map[i[1]++] = get_next_line(i[0]);
	mlx->map[i[1]] = NULL;
	i[1] = -1;
	while (mlx->height > ++i[1])
		if (check_identifier(mlx, i[1]))
			mlx->count++;
	if (mlx->count != 6)
		ft_putstr_fd("Errors In Edentifier \n", 2);
	if_edentifier_is_null(mlx);
	check_colors(mlx);
	if (!check_identifier_extension(mlx))
		ft_putstr_fd("Identifiers do not end with .xpm\n", 2);
	check_walls(mlx);
}

int	check_identifier_extension(t_mx *mlx)
{
	if (ft_strncmp(ft_strrchr(mlx->no, '.'), ".xpm", 4) != 0
		|| ft_strncmp(ft_strrchr(mlx->so, '.'), ".xpm", 4) != 0
		|| ft_strncmp(ft_strrchr(mlx->we, '.'), ".xpm", 4) != 0
		|| ft_strncmp(ft_strrchr(mlx->ea, '.'), ".xpm", 4) != 0)
	{
		return (0);
	}
	return (1);
}
