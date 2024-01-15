/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:58:19 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/23 14:22:02 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_continued(t_prompt *p, int should_free, char **path)
{
	p->i = -1;
	while (p->envp[++p->i])
	{
		if (!(ft_strncmp(p->envp[p->i], "PWD=", 4)) && path[4])
			ft_replace_in(&p->envp, path[4], p->i);
		else if (!(ft_strncmp(p->envp[p->i], "OLDPWD=", 7)) && path[2])
			ft_replace_in(&p->envp, path[2], p->i);
	}
	if (should_free)
	{
		free(p->pwd);
		p->pwd = path[1];
	}
}

int	ft_cd_continued(t_prompt *p, char **path, char *tmp)
{
	int	should_free;

	should_free = 1;
	path[3] = getcwd(NULL, 0);
	if (path[3] != NULL)
	{
		tmp = ft_strjoin("PWD=", path[3]);
		should_free = 1;
		path[1] = path[3];
	}
	else
	{
		free(path[3]);
		should_free = 0;
		path[1] = p->pwd;
		tmp = ft_strjoin("PWD=", p->pwd);
	}
	path[4] = tmp;
	free(tmp);
	ft_continued(p, should_free, path);
	free(path[2]);
	return (g_status);
}

int	ft_cd(t_prompt *p, char **full_cmd)
{
	char	*path[5];
	char	**str;
	char	*tmp;

	g_status = 0;
	tmp = NULL;
	str = full_cmd;
	path[3] = getcwd(NULL, 0);
	path[2] = ft_strjoin("OLDPWD=", path[3]);
	free(path[3]);
	if (str[1] == NULL)
	{
		tmp = mini_env("HOME", p->envp, 4);
		path[0] = tmp;
	}
	else
		path[0] = str[1];
	if (chdir(path[0]) == -1)
	{
		free(path[2]);
		return (mini_perror(NDIR, path[0], 1), 0, EXIT_FAILURE);
	}
	if (tmp)
		free(tmp);
	return (ft_cd_continued(p, path, tmp));
}
