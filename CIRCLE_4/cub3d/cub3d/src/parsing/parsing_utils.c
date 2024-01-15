/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:26:53 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/25 14:46:30 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_range(char **str)
{
	if (ft_strlen_2(str) != 3)
		return (1);
	if ((ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255)
		|| (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)
		|| (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255))
		return (1);
	return (0);
}

int	is_number(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (ft_strlen_2(str) != 3)
		return (1);
	while (str[i])
	{
		tmp = ft_strtrim(str[i], " \t\n");
		if (!tmp || ft_atoi(tmp) < 0 || ft_atoi(tmp) > 255
			|| !ft_isdigit(tmp[0]))
			return (1);
		j = -1;
		while (tmp[++j])
			if (!ft_isdigit(tmp[j]))
				return (1);
		free(tmp);
		i++;
	}
	return (0);
}

int	check_identifier_format(char **identifier)
{
	if (identifier[2] != NULL)
	{
		return (0);
	}
	if (identifier[1][0] == '\n')
	{
		return (0);
	}
	return (1);
}

int	ft_comma(char *s)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = ft_strtrim(s, " \t\n");
	if (!ft_isdigit(tmp[0]))
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == ',')
			len++;
		i++;
	}
	free(tmp);
	return (len);
}

void	check_colors(t_mx *mlx)
{
	char	**color1;
	char	**color2;

	if (ft_comma(mlx->f) != 2 || ft_comma(mlx->c) != 2)
		ft_putstr_fd("Errors In Colors\n", 2);
	color1 = ft_split(mlx->f, ',');
	color2 = ft_split(mlx->c, ',');
	if (is_number(color2) == 1 || is_number(color1) == 1)
		ft_putstr_fd("Errors In Colors\n", 2);
	free_tab(color1);
	free_tab(color2);
}
