/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:05:38 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 18:50:31 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_variable(const char *variable, char **environ)
{
	size_t	i;
	int		j;
	char	*test;

	i = 0;
	while (environ[i] != NULL)
	{
		test = ft_strdup(environ[i]);
		if (ft_strncmp(variable, environ[i], \
			big_len(ft_strlen(variable), ft_strlen(test))) == 0)
		{
			j = i;
			free(environ[j]);
			while (environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
			i--;
		}
		i++;
		free(test);
	}
}

int	ft_unset(t_mini *mini, char **envp)
{
	size_t	i;

	i = 1;
	while (i < ft_strlen_2(mini->full_cmd))
	{
		unset_variable(mini->full_cmd[i], envp);
		i++;
	}
	return (0);
}

void	sigin(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_status = 130;
	close(0);
	(void)signal;
	return ;
}
