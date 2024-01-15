# ifndef PARSER_H
# define PARSER_H

# define STDIN 0
# define STDOUT 1
#include "token.h"
# include "../libft/inc/libft.h"
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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
# endif
