/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:58:19 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/19 14:31:34 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	ft_cd(t_prompt	*p)
{
	char	*path[4];
	char	**str;

	str = ((t_mini *)p->cmds->content)->full_cmd;
	path[2] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (str[1] == NULL)
		path[0] = mini_env("HOME", p->envp, 4);
	else
		path[0] = str[1];
	if (chdir(path[0]) == -1)
		return (perror("minishell: cd:"), 0, EXIT_FAILURE);
	if (getcwd(NULL, 0) != NULL)
		path[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	else
		path[1] = p->pwd;
	p->i = -1;
	while (p->envp[++p->i])
	{
		if (!(ft_strncmp(p->envp[p->i], "PWD=", 4)) && path[1])
			ft_replace_in(&p->envp, path[1], p->i);
		else if (!(ft_strncmp(p->envp[p->i], "OLDPWD=", 7)) && path[2])
			ft_replace_in(&p->envp, path[2], p->i);
	}
	p->pwd = path[1];
	return (0);
}
