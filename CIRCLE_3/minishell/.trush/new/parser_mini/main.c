/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:16:53 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/09 18:39:22 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	g_status;

static t_prompt	init_prompt(char **argv, char **envp)
{
	(void) argv;
	t_prompt	prompt;

	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	return (prompt);
}

// void exece(t_prompt *p)
// {
// 	t_list				*cmds;
// 	t_mini				*mini;
// 	t_list				*list;

// 	list = p->cmds;
// 	// mini = list->content;
// 	if (ft_lstsize(list) > 1)
// 		multicmd(p);
// 	else if (ft_lstsize(list) == 1)
// 		exec(p);
// }
// int ft_cd(t_prompt	*p)
// {
// 	char	*path[3];
// 	char	**str;
// 	int		i;

//     path[0] = NULL;
// 	str = ((t_mini *)p->cmds->content)->full_cmd;
//     path[2] = ft_strjoin(ft_strdup("OLDPWD="), getcwd(NULL, 0));
//     if (str[1] == NULL)
//         path[0] = mini_env("HOME", p->envp, 4);
//     else
//         path[0] = str[1];
//     chdir(path[0]);
// 	path[1] = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
// 	i = -1;
// 	while (p->envp[++i])
// 	{
// 		if (!(ft_strncmp(p->envp[i], "PWD=", 4)))
// 			ft_replace_in(&p->envp, path[1], i);
// 		else if (!(ft_strncmp(p->envp[i], "OLDPWD=", 7)))
// 			ft_replace_in(&p->envp, path[2], i);
// 	}
// 	i = -1;
// 	while (p->envp[++i])
// 		printf("%s\n", p->envp[i]);
// 	return 0;
// }

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	t_prompt			*p;
	t_list				*cmds;
	t_mini				*mini;
	int					i;

	prompt = init_prompt(argv, envp);
	while (argv && argc)
	{
		out = readline("minishell: ");
		if (!(p = check_args(out, &prompt)))
			return 0;
		// exece(p)
		cmds = p->cmds;
		// ft_cd(p);
		// while (cmds)
		// {
		// 	mini = cmds->content;
		// 	i = -1;
		// 	printf("full_cmd: ");
		// 	while (mini->full_cmd[++i])
		// 		printf(" %s, ",mini->full_cmd[i]);
		// 	printf("\ninfile: %d\n outfile: %d\n full_path: %s\n", mini->infile, mini->outfile, mini->full_path);
		// 	printf("************************************************************************************\n");
		// 	cmds = cmds->next;
		// }
	}
}
// <Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile
