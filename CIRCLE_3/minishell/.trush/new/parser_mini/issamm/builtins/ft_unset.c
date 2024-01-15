/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:05:38 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/14 17:44:02 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"


void unset_variable(const char *variable, char **environ)
{
    size_t i;
	int	j;

	char *test;
	i = 0;
	while (environ[i] != NULL)
	{
		test = get_variable_name(environ[i]);
		 if (strncmp(variable, environ[i], big_len(ft_strlen(variable), ft_strlen(test))) == 0)
		  {
			j = i;
			while(environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
            i--;
        }
		i++;
    }
}

void	ft_unset(t_prompt *p)
{
	size_t i = 1;
	t_list	*lst;
	t_mini	*mini;

	lst = p->cmds;
	mini = lst->content;
	while(i < ft_strlen_2(mini->full_cmd))
	{
		unset_variable(mini->full_cmd[i], p->envp);
		i++;
	}
}
