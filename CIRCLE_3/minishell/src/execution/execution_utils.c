/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:12:42 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 14:22:02 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*ft_strnstr(const char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lendst;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = (char *)dst;
	if (!ptr && !len)
		return (NULL);
	lendst = ft_strlen(dst);
	if (len > lendst)
		len = lendst;
	while (len >= i)
	{
		if (ft_strncmp(ptr + i, src, ft_strlen(src)) == 0)
		{
			if (i + ft_strlen(src) > len)
				return (NULL);
			return (ptr + i);
		}
		else
			i++;
	}
	return (NULL);
}

void	ft_builtins(t_mini *mini, t_prompt *p, int flag)
{
	if (flag)
		input_output(mini);
	if (ft_strncmp(mini->full_cmd[0], "pwd", 3) == 0)
		g_status = ft_pwd(p->pwd);
	else if (ft_strncmp(mini->full_cmd[0], "env", 3) == 0)
		ft_env(p->envp);
	else if (ft_strncmp(mini->full_cmd[0], "cd", 2) == 0)
		ft_cd(p, mini->full_cmd);
	else if (ft_strncmp(mini->full_cmd[0], "echo", 4) == 0)
		g_status = ft_echo(mini);
	else if (ft_strncmp(mini->full_cmd[0], "exit", 4) == 0)
		ft_exit(mini->full_cmd);
	else if (ft_strncmp(mini->full_cmd[0], "unset", 5) == 0)
		g_status = ft_unset(mini, p->envp);
	else if (ft_strncmp(mini->full_cmd[0], "export", 6) == 0)
		ft_export(p, mini);
}

int	is_builtins(t_mini *mini)
{
	if (!mini->full_cmd)
		return (0);
	if ((ft_strncmp(mini->full_cmd[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "env\0", 4) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "cd\0", 3) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "echo\0", 5) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "exit\0", 5) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "unset\0", 6) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "export\0", 7) == 0))
		return (1);
	return (0);
}

void	dup_pipex(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
