/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:18:00 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/23 14:49:52 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = NULL;
	mini->infile = STDIN;
	mini->outfile = STDOUT;
	return (mini);
}

static t_mini	*params(t_mini *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '<' && a[0][*i][1] && a[0][*i][1] == '<')
			node = ft_infile_2(node, a, i);
		else if (a[0][*i][0] == '<')
			node = ft_infile_1(node, a, i);
		else if (a[0][*i][0] == '>' && a[0][*i][1] && a[0][*i][1] == '>')
			node = ft_outfile_2(node, a, i);
		else if (a[0][*i][0] == '>')
			node = ft_outfile_1(node, a, i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = ft_extend_matrix(node->full_cmd, a[1][*i]);
		else
		{
			mini_perror(PIPENDERR, NULL, 258);
			*i = -2;
		}
		return (node);
	}
	mini_perror(PIPENDERR, NULL, 258);
	*i = -2;
	return (node);
}

static char	**ft_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_dup_tab(args);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

static t_list	*ft_stop(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_free_tab(&temp);
	ft_free_tab(&args);
	return (NULL);
}

t_list	*ft_fill_lst(char **args, int i)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = ft_trimmed(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = params(cmds[1]->content, temp, &i);
		if (i < 0)
			return (ft_stop(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_free_tab(&temp[1]);
	ft_free_tab(&args);
	return (cmds[0]);
}
