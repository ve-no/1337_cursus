/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:50:46 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/19 20:09:17 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define STDIN 0
# define STDOUT 1
# include "libft/inc/libft.h"
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
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
	DUPERR = 5,
	FORKERR = 6,
	PIPERR = 7,
	PIPENDERR = 8,
	IS_DIR = 9,
	NOT_DIR = 10
};

char	*expand_path(char *str, int i, int quotes[2], char *var);
char	*expand_vars(char *prev, char *str, int i, t_prompt *prompt);
char	*mini_env(char *var, char **envp, int n);
int		malloc_len(char const *s1);
int		ft_unexpected(char c);
char	*ft_strtrim_all(char const *s1, int squote, int dquote);
t_mini	*get_infile2(t_mini *node, char **args[2], int *i);
t_mini	*get_infile1(t_mini *node, char **args[2], int *i);
t_mini	*get_outfile2(t_mini *node, char **args[2], int *i);
t_mini	*get_outfile1(t_mini *node, char **args[2], int *i);
int		get_fd(int *oldfd, char *path, int flags[2]);
void	ft_free_matrix(char ***m);
void	*mini_perror(int err_type, char *param, int err);
char	**ft_matrix_replace_in(char ***big, char **small, int n);
t_list	*fill_nodes(char **args, int i);
int		get_here_doc(char *str[2], char *aux[2]);
char	**ft_cmdtrim(char const *s, char *set);
char	*get_here_str(char *str[2], size_t len, char *limit, char *warn);
char	**ft_cmdsubsplit(char const *s, char *set);
void	*check_args(char *out, t_prompt *p);
void	free_content(void *content);
void	ft_export(t_prompt *p);
int		big_len(int s1, int s2);
char	*get_variable_name(char *str);
int		get_char_index(char *str, char c);
void	execution(t_prompt *p);

int		ft_cd(t_prompt	*p);
void	ft_pwd(char *pwd, char **cmds);
void	ft_env(t_prompt *p);
void	ft_echo(t_prompt *p);
void	ft_exit(t_prompt *p);
void	ft_unset(t_prompt *p);
#endif
