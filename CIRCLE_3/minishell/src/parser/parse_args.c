/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:16:16 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/23 18:55:50 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*mini_env(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

static char	**split_all(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];
	char	*tmp;

	tmp = "NULL";
	i = -1;
	while (args && args[++i])
	{
		args[i] = exp_path(args[i], -1, quotes, \
			mini_env("HOME", prompt->envp, 4));
		args[i] = exp_va(tmp, args[i], -1, prompt);
		subsplit = ft_subsplit(args[i], "<|>");
		ft_tab_replace_in(&args, subsplit, i);
		tmp = args[i];
		i += ft_strlen_2(subsplit) - 1;
		ft_free_tab(&subsplit);
	}
	return (args);
}

void	*check_args(char *out, t_prompt *p)
{
	char	**a;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	free(out);
	if (!a)
	{
		mini_perror(QUOTE, NULL, 1);
		return ("");
	}
	p->cmds = ft_fill_lst(split_all(a, p), -1);
	if (p->cmds)
		execution(p);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
