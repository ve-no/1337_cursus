/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:13:05 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 15:54:14 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*get_path_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (env[i] && env[i] + 5)
		return (env[i] + 5);
	return (NULL);
}

char	*return_path(const char *argv, char **env)
{
	int		i;
	char	**s;
	char	*ptr;
	char	*sss;

	s = ft_split(get_path_env(env), ':');
	i = 0;
	while (s && s[i])
	{
		ptr = ft_strjoin(s[i], "/");
		sss = ft_strjoin(ptr, (char *)argv);
		if (access(sss, F_OK) == 0)
		{
			while (s[++i])
				free(s[i]);
			free(s);
			return (sss);
		}
		free(sss);
		i++;
	}
	free(s);
	return (0);
}

int	search(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

int	exec_comm(t_prompt *p, t_mini *mini)
{
	char	*path;

	init_signal();
	if (!mini->full_cmd)
		exit(g_status);
	if (search(mini->full_cmd[0], '/') > -1)
		path = mini->full_cmd[0];
	else
		path = return_path(mini->full_cmd[0], p->envp);
	if (execve(path, mini->full_cmd, p->envp) == -1)
		return (mini_perror(NCMD, *mini->full_cmd, 127), exit(127), 127);
	return (0);
}

int	parent(int keeper, int *fdpipe)
{
	close(keeper);
	keeper = fdpipe[0];
	close(fdpipe[1]);
	return (keeper);
}
