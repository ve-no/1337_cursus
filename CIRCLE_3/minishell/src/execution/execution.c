/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:04:11 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/24 15:36:37 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	input_output(t_mini *mini)
{
	if (mini->infile)
	{
		dup2(mini->infile, 0);
		close(mini->infile);
	}
	if (mini->outfile > 1)
	{
		dup2(mini->outfile, 1);
		close(mini->outfile);
	}
}

void	child_process(t_mini *mini, t_list *list, int *fdpipe, t_prompt *p)
{
	if (mini->infile)
	{
		dup2(mini->infile, 0);
		close(mini->infile);
	}
	if (list->next != NULL)
	{
		dup2(fdpipe[1], 1);
		close(fdpipe[1]);
	}
	if (mini->outfile > 1)
	{
		dup2(mini->outfile, 1);
		close(mini->outfile);
	}
	close(fdpipe[0]);
	if (is_builtins(mini))
	{
		ft_builtins(mini, p, 0);
		exit(g_status);
	}
	else
		exec_comm(p, mini);
}

void	multiple_cmd(t_prompt *p, t_list *list, int keeper)
{
	int		fdpipe[2];
	t_mini	*mini;

	while (list)
	{
		mini = list->content;
		pipe(fdpipe);
		signal(SIGINT, SIG_IGN);
		p->pid = fork();
		if (p->pid == -1)
			failed_fork();
		if (p->pid == 0)
		{
			more_than_cmd(p->i, keeper);
			child_process(mini, list, fdpipe, p);
		}
		else
		{
			keeper = parent(keeper, fdpipe);
			list = list->next;
			p->i++;
		}
	}
	close(fdpipe[1]);
	close(fdpipe[0]);
}

void	waiting(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (pid != -1)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
	}
	while (wait(NULL) != -1)
		;
}

void	execution(t_prompt *p)
{
	int		keeper;
	int		tmpin;
	int		tmpout;
	t_list	*lst;
	t_mini	*mini;

	lst = p->cmds;
	mini = lst->content;
	if (ft_lstsize(lst) == 1 && is_builtins(mini))
	{
		ft_builtins(mini, p, 1);
		return ;
	}
	keeper = -2;
	p->i = 0;
	tmpin = dup(0);
	tmpout = dup(1);
	multiple_cmd(p, lst, keeper);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waiting(p->pid);
	init_signal();
}
