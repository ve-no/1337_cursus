/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:16:16 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/14 17:55:23 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern int	g_status;

char	*mini_env(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = strlen(var);
	while (!strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, strlen(envp[i])));
		i++;
	}
	return (NULL);
}

static char	**split_all(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes, \
			mini_env("HOME", prompt->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

// static void	*parse_args(char **args, t_prompt *p)
// {
// 	p->cmds = fill_nodes(split_all(args, p), -1);
// 	if (!p->cmds)
// 		return (p);
// 	return (p);
// }

static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;

	is_exit = 0;
	p->cmds = fill_nodes(split_all(args, p), -1);
	if (!p->cmds)
		return (p);
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_prompt *p)
{
	char	**a;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0])
		add_history(out);
	a = ft_cmdtrim(out, " \t");
	free(out);
	if (!a)
	{
		mini_perror(QUOTE, NULL, 1);
		return ("");
	}
	p = parse_args(a, p);
	// if (p && p->cmds)
	// 	n = p->cmds->content;
	// if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
	// 	p->envp = mini_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
	// 		p->envp, 1);
	// if (p && p->cmds)
	// 	ft_lstclear(&p->cmds, free_content);
	return (p);
}

