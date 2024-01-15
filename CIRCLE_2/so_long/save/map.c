/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:47:11 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/12 14:20:49 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	fill_matrix_and_check(t_data *data)
{
	while (1)
	{
		data->tmp = get_next_line(data->fd);
		if (!data->tmp)
			break ;
		data->line = ft_strjoin(data->line, data->tmp);
		data->height++;
		free(data->tmp);
	}
	free(data->tmp);
	if (!data->line || data->line[0] != '1'
		|| data->line[ft_strlen(data->line) - 1] != '1')
		return (0);
	data->map = ft_split(data->line, '\n');
	data->c_map = ft_split(data->line, '\n');
	data->width = ft_strlen(data->map[0]);
	if (!check_wall(data) || !check_content_map(data, -1) || !data->line
		|| !data->c_map || !data->map)
		return (0);
	free(data->line);
	search(data);
	valid_path(data->c_map, data->p_x, data->p_y, "P0C");
	valid_path(data->c_map, data->p_x, data->p_y, "BE");
	return (path_is_valid(data->c_map));
}

void	valid_path(char **map, int x, int y, char *s)
{
	char	fill;

	if (s[0] == 'P')
		fill = 'B';
	else
		fill = '1';
	if (!ft_strchr(s, map[y][x]))
		return ;
	map[y][x] = fill;
	valid_path(map, x + 1, y, s);
	valid_path(map, x - 1, y, s);
	valid_path(map, x, y + 1, s);
	valid_path(map, x, y - 1, s);
}

int	map(t_data *data, char *arg)
{
	if (ft_rcmp(arg, ".ber"))
		return (write_err(2, NULL));
	data->fd = open(arg, O_RDONLY);
	if (data->fd == -1)
		return (write_err(3, data));
	if (!fill_matrix_and_check(data))
		return (write_err(1, NULL));
	return (1);
}
