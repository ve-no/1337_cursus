/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:07:46 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 14:22:02 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	else if (!str[1])
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(t_mini *mini)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	if (mini->full_cmd[0] != NULL)
	{
		while (mini->full_cmd[++i])
		{
			if (check_flag(mini->full_cmd[i]))
			{
				flag = 1;
				continue ;
			}
			printf("%s", mini->full_cmd[i]);
			if (i != (int)ft_strlen_2(mini->full_cmd) - 1)
				printf(" ");
		}
	}
	if (!flag)
		printf("\n");
	return (0);
}
