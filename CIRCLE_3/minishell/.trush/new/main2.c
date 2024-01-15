#include "parser.h"

int main(int ac, char **av, char **env)
{
	char **strtrim = split_string(readline("$minishell: "), " ");
	int len = ft_matrixlen(strtrim), i = -1, quotes[2];
	char **subsplit;
	while (strtrim[++i])
	{
		strtrim[i] = expand_vars(strtrim[i], -1, quotes, env);
		strtrim[i] = expand_path(strtrim[i], -1, quotes, mini_env("HOME", env, 4));
		subsplit = ft_cmdsubsplit(strtrim[i], "<|>");
		ft_matrix_replace_in(&strtrim, subsplit, i);
		strtrim[i] = ft_strtrim_all(strtrim[i], 0, 0);
	}
	i = -1;
	while (strtrim[++i])
		printf("%s\n", strtrim[i]);
}
