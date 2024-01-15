/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:53:46 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/15 11:06:28 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void ft_exit_helper(t_mini *mini)
{
	int i = 0;
	while (mini->full_cmd[1][i])
	{
		if ((mini->full_cmd[1][i] >= 'a' && mini->full_cmd[1][i] <= 'z') ||
			(mini->full_cmd[1][i] >= 'A' && mini->full_cmd[1][i] <= 'Z'))
		{
			printf("exit: %s: numeric argument required\n", mini->full_cmd[0]);
			g_status = 255;
			exit(g_status);
		}
		i++;
	}
	exit(ft_atoi(mini->full_cmd[1]));
}

void ft_exit(t_prompt *p)
{
	t_list *lst;
	t_mini *mini;
	int i = 0;
	int j = 1;

	lst = p->cmds;
	mini = lst->content;

	if (ft_strlen_2(mini->full_cmd) == 1)
		exit(g_status);
	else if (ft_strlen_2(mini->full_cmd) > 2)
	{
		while (mini->full_cmd[j][i])
		{
			j = 1;
			while (mini->full_cmd[j][i])
			{
				if ((mini->full_cmd[j][i] >= 'a' && mini->full_cmd[j][i] <= 'z') ||
					(mini->full_cmd[j][i] >= 'A' && mini->full_cmd[j][i] <= 'Z'))
				{
					printf("exit: %s: numeric argument required\n", mini->full_cmd[0]);
					g_status = 255;
					exit(g_status);
				}
				i++;
			}
		}
		printf("exit: %s: too many arguments\n", mini->full_cmd[0]);
		g_status = 1;
	}
	else
		ft_exit_helper(mini);
}
