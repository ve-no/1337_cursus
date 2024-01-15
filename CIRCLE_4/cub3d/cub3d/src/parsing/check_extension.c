/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 08:45:56 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/25 13:15:42 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free(char **s, int *i)
{
	while (*i >= 0)
	{
		free(s[*i]);
		(*i)--;
	}
	free(s);
}

void	check_extension(int ac, char *str)
{
	int		i;
	char	**s;

	i = 0;
	if (ac != 2)
		ft_putstr_fd("Error in argument \n", 2);
	else
	{
		s = ft_split(str, '.');
		while (s[i])
			i++;
		if (ft_strncmp(s[i - 1], "cub", 4) == 0)
		{
			ft_free(s, &i);
			return ;
		}
		else
		{
			ft_free(s, &i);
			write(2, "Error\n", 6);
			ft_putstr_fd("The Map Doesn't end with .cub\n", 2);
		}
	}
}

int	rgb_to_decimal(char *s)
{
	char	**color;
	int		red;
	int		green;
	int		blue;
	int		decimal_value;

	color = ft_split(s, ',');
	red = ft_atoi(color[0]);
	green = ft_atoi(color[1]);
	blue = ft_atoi(color[2]);
	decimal_value = (red << 16) + (green << 8) + blue;
	free_tab(color);
	return (decimal_value);
}

void	if_edentifier_is_null(t_mx *mlx)
{
	if (mlx->no == NULL || mlx->so == NULL || mlx->we == NULL
		|| mlx->ea == NULL || mlx->f == NULL || mlx->c == NULL)
		ft_putstr_fd("Errors In Map \n", 2);
}

int	is_facing(int facing)
{
	if (facing)
		return (-1);
	return (0);
}
