/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:31:23 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/14 18:48:16 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern int	g_status;

int ft_unexpected(char c)
{
	char	*unex;

	unex = "#;.*()&>|<`";
	while (*unex)
	{
		if (*unex == c)
			return (1);
		unex++;
	}
	return (0);
}
void	*mini_perror(int err_type, char *param, int err)
{
	g_status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

int	get_fd(int *oldfd, char *path, int flags[2])
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

t_mini	*get_outfile1(t_mini *node, char **args[2], int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	// printf("hi from std :%s\t%c:\n",args[1][(*i)], args[0][*i][0]);
	if (args[1][*i] && !ft_unexpected(args[0][*i][0]))
		node->outfile = get_fd(&node->outfile, args[1][*i], flags);
	if (!args[1][*i] || node->outfile == -1 || ft_unexpected(args[0][*i][0]))
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 258;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_outfile2(t_mini *node, char **args[2], int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	// printf("hi from std %s\n",args[1][(*i)]);

	if (args[1][++(*i)] && !ft_unexpected(args[0][*i][0]))
		node->outfile = get_fd(&node->outfile, args[1][*i], flags);
	if (!args[1][*i] || node->outfile == -1 || ft_unexpected(args[0][*i][0]))
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 258;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_infile1(t_mini *node, char **args[2], int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[1][*i] && !ft_unexpected(args[0][*i][0]))
		node->infile = get_fd(&node->infile, args[1][*i], flags);
	if (!args[1][*i] || node->infile == -1 || ft_unexpected(args[0][*i][0]))
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 258;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_infile2(t_mini *node, char **args[2], int *i)
{
	char	*aux[2];
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	nl = "minishell: syntax error near unexpected token `newline'";
	if (args[1][++(*i)] && !ft_unexpected(args[0][*i][0]))
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
			g_status = 258;
		}
	}
	return (node);
}

void	free_content(void *content)
{
	t_mini	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN)
		close(node->infile);
	if (node->outfile != STDOUT)
		close(node->outfile);
	free(node);
}
