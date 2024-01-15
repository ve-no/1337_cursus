/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:51:11 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/17 11:22:44 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	write_err(int c, t_data *map)
{
	write(2, WHT "ERROR :\n\t", 16);
	if (c == 0)
		write(2, RED "INVALID ARGUMENT TRY ./so_long <PATH>'\n", 49);
	if (c == 1)
		write(2, RED "SOMETHING ELSE IN MAP \n", 30);
	if (c == 2)
		write(2, RED "INVALID SIGNIFIES TRY '.ber' IN END OF YOUR FILE NAME\n",
			62);
	if (c == 3)
	{
		write(2, RED "FILE NOT FOUND TRY 'map.ber'\n", 36);
		close(map->fd);
	}
	if (c == 4)
		write(2, RED "FILE IMAGE NOT FOUND PLS ADD THE PATH OF IMAGES\n", 55);
	return (0);
}

void	search(t_data *data)
{
	data->j = 0;
	while (data->map[data->j])
	{
		data->i = 0;
		while (data->map[data->j][++data->i])
		{
			if (data->map[data->j][data->i] == 'P')
			{
				data->p_x = data->i;
				data->p_y = data->j;
			}
		}
		data->j++;
	}
	data->i = 0;
	data->j = 0;
}

int	check_wall(t_data *map)
{
	char	*str;

	map->i = -1;
	while (map->map[0][++map->i])
		if (map->map[0][map->i] != '1' || map->map[map->height
			- 1][map->i] != '1')
			return (0);
	map->i = -1;
	while (map->map[++map->i])
	{
		str = map->map[map->i];
		if (str[map->width - 1] != '1' || str[0] != '1'
			|| (int)ft_strlen(str) != map->width)
			return (0);
	}
	return (1);
}

int	check_content_map(t_data *map, int i)
{
	char	*str;

	map->check = ft_calloc(1, sizeof(t_valid));
	while (map->map[++i])
	{
		str = map->map[i];
		map->j = -1;
		while (str[++map->j])
		{
			if (str[map->j] == '1' || str[map->j] == '0' || str[map->j] == 'Z')
				map->check->wall = 1;
			else if (str[map->j] == 'C')
				map->check->coins++;
			else if (str[map->j] == 'P')
				map->check->player++;
			else if (str[map->j] == 'E')
				map->check->exit++;
			else
				return (0);
		}
	}
	if (map->check->coins < 1 || map->check->player!= 1 || map->check->wall != 1
		|| map->check->exit != 1)
		return (0);
	return (1);
}

int	path_is_valid(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (ft_strchr(map[i], 'C') || ft_strchr(map[i], 'E'))
			return (0);
	}
	return (1);
}
