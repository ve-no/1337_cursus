# ifndef PARSER_H
# define PARSER_H

# define STDIN 0
# define STDOUT 1


# include "libft/inc/libft.h"
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int	infile;
	int	outfile;
}		t_mini;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

char	*expand_path(char *str, int i, int quotes[2], char *var);
char	*expand_vars(char *str, int i, int quotes[2], char **env);
char	*mini_env(char *var, char **envp, int n);
int		malloc_len(char const *s1);
char	*ft_strtrim_all(char const *s1, int squote, int dquote);
t_mini	*get_infile2(t_mini *node, char **args, int *i);
t_mini	*get_infile1(t_mini *node, char **args, int *i);
t_mini	*get_outfile2(t_mini *node, char **args, int *i);
t_mini	*get_outfile1(t_mini *node, char **args, int *i);
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

# endif
