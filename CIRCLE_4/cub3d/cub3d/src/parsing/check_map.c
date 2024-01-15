/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:31:45 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/25 13:03:56 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	height_map2(t_mx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mlx->height > i)
	{
		if (ft_strncmp(mlx->map[i], "NO", 2) == 0
			|| ft_strncmp(mlx->map[i], "SO", 2) == 0
			|| ft_strncmp(mlx->map[i], "WE", 2) == 0
			|| ft_strncmp(mlx->map[i], "EA", 2) == 0
			|| ft_strncmp(mlx->map[i], "F", 1) == 0
			|| ft_strncmp(mlx->map[i], "C", 1) == 0
			|| mlx->map[i][j] == '\n')
				i++;
		else
			return (i);
	}
	return (i);
}

void	check_the_player(t_mx *mlx, int *len, int i, int j)
{
	if (ft_strchr("NWES", mlx->map2[i][j]))
	{
		mlx->x = i;
		mlx->y = j;
		mlx->p_dir = mlx->map2[i][j];
		(*len)++;
	}
}

void	check_the_map(t_mx *mlx, int i, int len, int j)
{
	while (mlx->map2[++i])
	{
		j = -1;
		while (mlx->map2[i][++j])
		{
			check_the_player(mlx, &len, i, j);
			if (!ft_strchr("NWES10 ", mlx->map2[i][j]))
				ft_putstr_fd("Errors in map \n", 2);
			if (mlx->map2[i][j] == '0' || mlx->map2[i][j] == mlx->p_dir)
			{
				if (j > (int)ft_strlen(mlx->map2[i + 1]) || i == 0
					|| j == 0 || j > (int)ft_strlen(mlx->map2[i - 1]))
					ft_putstr_fd("Player can't go outside\n", 2);
				if (mlx->map2[i][j - 1] == ' ' || mlx->map2[i][j - 1] == '\0'
					|| mlx->map2[i][j + 1] == ' ' || mlx->map2[i][j + 1] == '\0'
					|| mlx->map2[i - 1][j] == ' ' || mlx->map2[i - 1][j] == '\0'
					|| mlx->map2[i + 1][j] == ' ' || mlx->map2[i + 1][j] == '\0'
					)
					ft_putstr_fd("Errors in map \n", 2);
			}
		}
	}
	if (len != 1)
		ft_putstr_fd("Errors in player\n", 2);
}

void	complete_map(t_mx *mlx)
{
	int		j;
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	len = 0;
	while (mlx->map2_height > i)
	{
		tmp = ft_strtrim(mlx->map[mlx->j++], "\n");
		mlx->map2[mlx->i++] = tmp;
		i++;
	}
	mlx->map2[mlx->i] = NULL;
	mlx->width = get_long_line(mlx->map2);
	i = -1;
	len = 0;
	check_the_map(mlx, i, len, j);
	mlx->height = mlx->i - 1;
}

void	check_walls(t_mx *mlx)
{
	int	i;

	i = -1;
	mlx->j = height_map2(mlx);
	mlx->map2_height = mlx->height - mlx->j;
	mlx->map2 = malloc(sizeof(char *) * (mlx->map2_height + 1));
	mlx->i = 0;
	complete_map(mlx);
}
