/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:31:23 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/23 15:39:47 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	ft_fd(int *oldfd, char *path, int flags[2])
{
	int	fd;

	if (*oldfd > 2)
		close(*oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		mini_perror(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		mini_perror(NPERM, path, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mini_perror(NPERM, path, 126);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && *oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = *oldfd;
	return (fd);
}

t_mini	*ft_outfile_1(t_mini *node, char **args[2], int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[1][*i] && !ft_unexpected(args[0][*i][0]))
		node->outfile = ft_fd(&node->outfile, args[1][*i], flags);
	if (!args[1][*i] || node->outfile == -1 || ft_unexpected(args[0][*i][0]))
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*ft_outfile_2(t_mini *node, char **args[2], int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	if (!(ft_strlen(args[0][*i]) > 2) && args[1][++(*i)]
		&& !ft_unexpected(args[0][*i][0]))
		node->outfile = ft_fd(&node->outfile, args[1][*i], flags);
	if (!args[1][*i] || node->outfile == -1 || ft_unexpected(args[0][*i][0]))
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*ft_infile_1(t_mini *node, char **args[2], int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[1][*i] && !ft_unexpected(args[0][*i][0]))
		node->infile = ft_fd(&node->infile, args[1][*i], flags);
	if (!args[1][*i] || node->infile == -1 || ft_unexpected(args[0][*i][0]))
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*ft_infile_2(t_mini *node, char **args[2], int *i)
{
	char	*aux[2];
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning";
	nl = "minishell: syntax error near unexpected token `newline'";
	if (!(ft_strlen(args[0][*i]) > 2) && args[1][++(*i)]
		&& !ft_unexpected(args[0][*i][0]))
	{
		aux[0] = args[1][*i];
		node->infile = get_here_doc(str, aux);
	}
	if (!args[1][*i] || node->infile == -1 || ft_unexpected(args[0][*i][0]))
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
	}
	return (node);
}
