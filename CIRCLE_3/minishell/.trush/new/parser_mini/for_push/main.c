/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:16:53 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/14 18:04:34 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	g_status;

static t_prompt	init_prompt(char **envp)
{
	t_prompt	prompt;

	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
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

int	exec_comm(t_prompt *p, t_mini *mini)
{
	char	*path;

		if (!mini->full_cmd)
			exit(0);
		if (search(mini->full_cmd[0], '/') > -1)
			path = mini->full_cmd[0];
		else
		{
			path = return_path(mini->full_cmd[0], p->envp);
		}
		execve(path, mini->full_cmd, p->envp);
		return (perror("command not found"), exit(127), EXIT_FAILURE);
}

void	dup_pipex(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

int	get_char_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (i);
}

char	*get_variable_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;

	int len =  get_char_index(str, '=');
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while (++i < len)
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

int	big_len(int s1, int s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}


void ft_export(t_prompt *p)
{
	char	*variable = NULL;
	char	*value = NULL;
	char	**environ;
	t_list *list;
	t_mini	*mini;
	char	**str;

	list =p->cmds;
	mini = list->content;
	environ = p->envp;
	if(mini->full_cmd[1] == NULL)
	{
		int i = 0;
		while(environ[i])
		{
			printf("declare -x ");
			printf("%s\n", environ[i]);
			i++;
		}
		return ;
	}

	int i = 1;
	str = ft_split(mini->full_cmd[1], '=');
	while (str[i])
	{
		value = ft_strjoin(value, str[i]);
		if(str[i + 1])
			value = ft_strjoin(value, "=");
		i++;
	}
	variable = str[0];
	if (!ft_isalpha(variable[0]))
	{
		printf("export: `%s': not a valid identifier\n", variable);
		return;
	}
	char *test;
    for (int i = 0; environ[i] != NULL; i++)
	{

		test = get_variable_name(environ[i]);
        if (strncmp(variable, test, big_len(ft_strlen(variable), ft_strlen(test))) == 0)
        {
            // Variable already exists, replace its value if value is provided
            if (value != NULL)
            {
                char *export = malloc(strlen(variable) + strlen(value) + 2); // for '=' w '\n'
                if (!export)
                {
                    printf("failed allocatin\n");
                    exit(0);
                }
                snprintf(export, strlen(variable) + strlen(value) + 2, "%s=%s", variable, value);
                // free(environ[i]); // hadi gha tkhasni darouri htach env dyalna m allocine liha
	            p->envp[i] = export;
			}
			return ;
		}
	}

   // Variable does not exist, append it to the environment variables if value is provided
        if (value != NULL)
        {
            size_t export_length = strlen(variable) + strlen(value) + 2;
            char *export = malloc(export_length);
            snprintf(export, export_length, "%s=%s", variable, value);
            int num_variables = 0;
            while (environ[num_variables] != NULL)
                num_variables++;
            char **env = malloc((num_variables + 3) * sizeof(char *));
			int i = -1;
            while(environ[++i])
                env[i] = environ[i];
            env[num_variables] = export;
            env[num_variables + 1] = NULL;
			p->envp = env;
        }
        else
        {
            char *export = malloc(strlen(variable) + 1);
            int num_variables = 0;
            while (environ[num_variables] != NULL)
                num_variables++;
            export = variable;
            char **env = malloc((num_variables + 2) * sizeof(char *));
            int i = -1;
            while(environ[++i])
                env[i] = environ[i];
            env[num_variables] = export;
            env[num_variables + 1] = NULL;
			p->envp = env;
        }
}

void	ft_builtins(t_prompt *p)
{
	t_list	*list;
	t_mini	*mini;

	list = p->cmds;
	mini = list->content;

	if (ft_strncmp(mini->full_cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(mini->full_cmd[0], "env", 3) == 0)
		ft_env(p);
	else if (ft_strncmp(mini->full_cmd[0], "cd", 2) == 0)
		ft_cd(p);
	else if (ft_strncmp(mini->full_cmd[0], "echo", 4) == 0)
		ft_echo(p);
	// else if (ft_strncmp(mini->full_cmd[0], "exit", 4) == 0)
	// 	ft_exit();
	// else if (ft_strncmp(mini->full_cmd[0], "unset", 5) == 0)
	// 	ft_unset();
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
		|| (ft_strncmp(mini->full_cmd[0], "cd\0", 4) == 0)
		|| (ft_strncmp(mini->full_cmd[0], "echo\0", 5) == 0)
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

	if (!ft_strlen((const char *)p))
		return ;
	list = p->cmds;

	int tmpin=dup(0);
	int tmpout=dup(1);//set the initial input
	int id;
	int i = 0;
	static int		keeper = -2;
	int	fdpipe[2];
	if (ft_lstsize(list) == 1 && is_builtins(p))
		ft_builtins(p);
	else
	{
		while(list)
		{
			mini = list->content;
			pipe(fdpipe);
			id = fork();
			if (id == -1) {
				printf("minishell: fork: Resource temporarily unavailable\n");
				exit(1);
			}
			if (id  == 0)
			{
				if (i != 0) /// fatet l cmd lawla
					dup2(keeper, 0);
				if (mini->infile)
				{
					dup2(mini->infile, 0);
					close(mini->infile);
				}
				if (ft_lstsize(list) > 1)
					dup2(fdpipe[1], 1);
				if (mini->outfile)
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
		while (wait(NULL) != -1)
		;
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
	}
}
int	main(int argc, char **argv, char **envp)
{
	char				*out;
	t_prompt			prompt;
	t_prompt			*p;

	(void) argc;
	(void) argv;
	prompt = init_prompt(envp);
	while (1)
	{
		out = readline("minishell: ");
		if (!(p = check_args(out, &prompt)))
			return 0;
		execution(p);
		ft_lstclear(&p->cmds, free_content);
		// system("leaks minishell");
	}

}
