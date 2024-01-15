/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:53:46 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 14:22:02 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_helper(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[1][i])
	{
		if ((cmd[1][i] >= 'a' && cmd[1][i] <= 'z') ||
			(cmd[1][i] >= 'A' && cmd[1][i] <= 'Z'))
		{
			printf("minishell: %s: numeric argument required\n", cmd[0]);
			g_status = 255;
			exit(g_status);
		}
		i++;
	}
	exit(ft_atoi(cmd[1]));
}

void	ft_exit(char **cmd)
{
	int		i;
	int		j;

	i = -1;
	j = 1;
	if (ft_strlen_2(cmd) == 1)
		exit(g_status);
	else if (ft_strlen_2(cmd) > 2)
	{
		while (cmd[j][++i])
		{
			if ((cmd[j][i] >= 'a' && cmd[j][i] <= 'z')
			|| (cmd[j][i] >= 'A' && cmd[j][i] <= 'Z'))
			{
				printf("minishell: %s: numeric argument required\n",
					cmd[0]);
				g_status = 255;
				exit(g_status);
			}
		}
		printf("minishell: %s: too many arguments\n", cmd[0]);
		g_status = 1;
	}
	else
		ft_exit_helper(cmd);
}

void	more_than_cmd(int b, int keeper)
{
	if (b != 0)
	{
		dup2(keeper, 0);
		close(keeper);
	}
}
