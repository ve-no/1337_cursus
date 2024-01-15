/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:55:06 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/23 18:42:08 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# include "../libft/inc/libft.h"
// # include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# define BLUE "\001\033[1;94m\002"
# define WHITE "\001\033[0;97m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"

int	g_status;
typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	char	*pwd;
	pid_t	pid;
	int		i;
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_mini;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 4,
	PIPERR = 7,
	PIPENDERR = 8
};

char	*exp_path(char *str, int i, int quotes[2], char *var);
char	*exp_va(char *prev, char *str, int i, t_prompt *prompt);
char	*mini_env(char *var, char **envp, int n);
int		malloc_len(char const *s1);
int		ft_unexpected(char c);
char	*ft_strtrim_all(char const *s1, int squote, int dquote);
t_mini	*ft_infile_2(t_mini *node, char **args[2], int *i);
t_mini	*ft_infile_1(t_mini *node, char **args[2], int *i);
t_mini	*ft_outfile_2(t_mini *node, char **args[2], int *i);
t_mini	*ft_outfile_1(t_mini *node, char **args[2], int *i);
int		ft_fd(int *oldfd, char *path, int flags[2]);
void	ft_free_tab(char ***m);
void	*mini_perror(int err_type, char *param, int err);
char	**ft_tab_replace_in(char ***big, char **small, int n);
t_list	*ft_fill_lst(char **args, int i);
int		get_here_doc(char *str[2], char *aux[2]);
char	**ft_cmdtrim(char const *s, char *set);
char	*get_here_str(char *str[2], size_t len, char *limit, char *warn);
char	**ft_subsplit(char const *s, char *set);
void	*check_args(char *out, t_prompt *p);
void	free_content(void *content);

int		big_len(int s1, int s2);
char	*get_variable_name(char *str);
int		get_index(char *str, char c);
void	execution(t_prompt *p);

void	signal_handle(int signal);
// builtins
int		ft_cd(t_prompt *p, char **full_cmd);
int		ft_pwd(char *pwd);
void	ft_env(char **p);
int		ft_echo(t_mini *mini);
void	ft_exit(char **cmd);
int		ft_unset(t_mini *mini, char **envp);
void	ft_export(t_prompt *p, t_mini *mini);
////////execution///////////
char	*ft_strnstr(const char *dst, const char *src, size_t len);
char	*get_path_env(char **env);
char	*return_path(const char *argv, char **env);
int		search(char *str, char c);
int		exec_comm(t_prompt *p, t_mini *mini);
void	dup_pipex(int oldfd, int newfd);
void	failed_fork(void);
void	execution(t_prompt *p);
void	signal_handler(int signal);
void	init_signal(void);
void	input_output(t_mini *mini);
void	ft_builtins(t_mini *mini, t_prompt *p, int flag);
int		is_builtins(t_mini *mini);
/////
char	*ft_strtrimfree(char *s1, char const *set);
int		check_set(char const *set, int s);
int		check_alpha(char *cmd);
char	*ft_strjoinfree(char *s1, char *s2);
char	*get_variable_from_cmd(char *cmd);
char	*get_variable_name(char *str);
int		get_index(char *str, char c);
char	*get_value_name(char *str);
void	value_exist(char *variable, char *value, char **environ, t_prompt *p);
void	append_new_variable(t_prompt *p, char *variable, char *value);
void	print(char **environ, int test);
void	bubble_sort(char *environ[], int size);
void	print_export(char **environ);
void	failed_fork(void);
int		parent(int keeper, int *fdpipe);
void	failed_allocation(void);
int		my_snprintf(char *str, size_t size, const char *format, ...);
char	*get_value(char *str, char *stre, char *value);
char	*value_exist_without_plus(char *variable, char *value,
			char *environ, char *envp);
char	*value_exist_with_plus(char *environ, char *value,
			char *variable, char *envp);
void	sigin(int signal);
void	more_than_cmd(int b, int keeper);
#endif
