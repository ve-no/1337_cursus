/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:58:19 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/11 15:18:05 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int ft_cd(t_prompt	*p)
{
	char	*path[3];
	char	**str;
	int		i;

    path[0] = NULL;

	str = ((t_mini *)p->cmds->content)->full_cmd;
    path[2] = ft_strjoin(ft_strdup("OLDPWD="), getcwd(NULL, 0));
    if (str[1] == NULL)
        path[0] = mini_env("HOME", p->envp, 4);
    else
        path[0] = str[1];
    if(chdir(path[0]) == -1)
	{
		printf("cd: %s: No such file or directory\n", path[0]);
		return(0);
	}
	path[1] = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
	i = -1;
	while (p->envp[++i])
	{
		if (!(ft_strncmp(p->envp[i], "PWD=", 4)))
			ft_replace_in(&p->envp, path[1], i);
		else if (!(ft_strncmp(p->envp[i], "OLDPWD=", 7)))
			ft_replace_in(&p->envp, path[2], i);
	}
	return 0;
}
