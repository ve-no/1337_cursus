/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:16:53 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/19 20:03:43 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern int	g_status;

static t_prompt	init_prompt(char **envp)
{
	t_prompt	prompt;

	g_status = 0;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	prompt.pwd = mini_env("PWD", prompt.envp, 3);
	return (prompt);
}

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

char	*get_path_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (env[i] && env[i] + 5)
		return (env[i] + 5);
	return (NULL);
}

char	*return_path(const char *argv, char **env)
{
	int		i;
	char	**s;
	char	*ptr;
	char	*sss;

	s = ft_split(get_path_env(env), ':');
	i = 0;
	while (s && s[i])
	{
		ptr = ft_strjoin(s[i], "/");
		sss = ft_strjoin(ptr, (char *)argv);
		if (access(sss, F_OK) == 0)
		{
			while (s[++i])
				free(s[i]);
			free(s);
			return (sss);
		}
		free(sss);
		i++;
	}
	free(s);
	return (0);
}

int	search(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

void	exec_comm(t_prompt *p, t_mini *mini)
{
	char	*path;

		if (!mini->full_cmd)
			exit(0);
		if (search(mini->full_cmd[0], '/') > -1)
			path = mini->full_cmd[0];
		else
			path = return_path(mini->full_cmd[0], p->envp);
		execve(path, mini->full_cmd, p->envp);
		mini_perror(NCMD, *mini->full_cmd, 127);
		return exit(127);
		// return (perror("command not found"), exit(127), EXIT_FAILURE);
}

void	dup_pipex(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

void	ft_builtins(t_prompt *p)
{
	t_list	*list;
	t_mini	*mini;

	list = p->cmds;
	mini = list->content;

	if (ft_strncmp(mini->full_cmd[0], "pwd", 3) == 0)
		ft_pwd(p->pwd, mini->full_cmd);
	else if (ft_strncmp(mini->full_cmd[0], "env", 3) == 0)
		ft_env(p);
	else if (ft_strncmp(mini->full_cmd[0], "cd", 2) == 0)
		ft_cd(p);
	else if (ft_strncmp(mini->full_cmd[0], "echo", 4) == 0)
		ft_echo(p);
	else if (ft_strncmp(mini->full_cmd[0], "exit", 4) == 0)
		ft_exit(p);
	else if (ft_strncmp(mini->full_cmd[0], "unset", 5) == 0)
		ft_unset(p);
	else if (ft_strncmp(mini->full_cmd[0], "export", 6) == 0)
		ft_export(p);
}

int	is_builtins(t_prompt *p)
{
	t_list	*list;
	t_mini	*mini;

	list = p->cmds;
	mini = list->content;
	if (!mini->full_cmd)
			return (0);
	if ((ft_strncmp(mini->full_cmd[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "env\0", 4) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "cd\0", 3) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "echо\0", 6) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "exit\0", 5) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "unset\0", 6) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "export\0", 7) == 0))
		return (1);
	return (0);
}

void execution(t_prompt *p)
{
    t_mini                *mini;
    t_list                *list;

	list = p->cmds;

	int tmpin=dup(0);
	int tmpout=dup(1);//set the initial input
	// int id;
	int i = 0;
	static int		keeper = -2;
	int	fdpipe[2];
	if (ft_lstsize(list) == 1 && is_builtins(p))
	{
		mini = list->content;
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
		ft_builtins(p);
	}
	else
	{
		while(list)
		{
			mini = list->content;
			pipe(fdpipe);
			p->pid = fork();
			if (p->pid == -1) {
				printf("minishell: fork: Resource temporarily unavailable\n");
				exit(1);
			}
			if (p->pid  == 0)
			{
				if (i != 0)
					dup2(keeper, 0);
				if (mini->infile)
				{
					dup2(mini->infile, 0);
					close(mini->infile);
				}
				if (ft_lstsize(list) > 1)
					dup2(fdpipe[1], 1);
				if (mini->outfile > 1)
					dup2(mini->outfile, 1);
				close(fdpipe[0]);
				exec_comm(p, mini);
			}
			else
			{
				close(keeper);
				keeper = fdpipe[0];
				close(fdpipe[1]);
				list = list->next;
				i++;
			}
		}
	}
		while (wait(NULL) != -1)
		;
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
}


char	*mini_prompt (t_prompt *p)
{
		char	*str;
		char	*m_p;
		char	*tmp;
		str = mini_env("PWD", p->envp, 3);
		tmp = ft_strrchr(str, '/') + 1;
		free(str);
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
		return tmp;
}

int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	t_prompt			*p;
	char				*str;

	(void) argc;
	(void) argv;
	prompt = init_prompt(envp);
	while (1)
	{
		str = mini_prompt(&prompt);
		out = readline(str);
		if (!(p = check_args(out, &prompt)))
			break ;
		free(str);
		// g_status = 0;
		// system("leaks minishell");
	}
}
