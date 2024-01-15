/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:16:53 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/24 15:40:09 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static t_prompt	init_prompt(char **envp)
{
	t_prompt	prompt;

	g_status = 0;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_tab(envp);
	prompt.pwd = mini_env("PWD", prompt.envp, 3);
	return (prompt);
}

void	signal_handler(int signal)
{
	(void)signal;
	if (g_status != 130)
		ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

char	*mini_prompt(t_prompt *p)
{
	char	*str;
	char	*m_p;
	char	*tmp;

	if (!p->pwd)
		return (ft_strdup("minishell: "));
	str = p->pwd;
	tmp = ft_strrchr(str, '/') + 1;
	m_p = ft_strjoin(BLUE, tmp);
	if (g_status)
		tmp = ft_strjoin(m_p, RED);
	else
		tmp = ft_strjoin(m_p, BLUE);
	free(m_p);
	m_p = ft_strjoin(tmp, " $\001\033[0;97m\002 ");
	free(tmp);
	tmp = ft_strjoin("\001\033[1;92m\002➜ @minishell  ", m_p);
	free(m_p);
	return (tmp);
}

int	main(int argc, char **argv, char **envp)
{
	char		*out;
	t_prompt	prompt;
	t_prompt	*p;
	char		*str;

	(void)argc;
	(void)argv;
	if (envp)
		prompt = init_prompt(envp);
	init_signal();
	while (1)
	{
		str = mini_prompt(&prompt);
		out = readline(str);
		p = check_args(out, &prompt);
		if (!p)
			break ;
		free(str);
	}
	exit(g_status);
}
