#include <stdio.h>
#include "include/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>

// char* expand_variable(char *var)
// {
// 	char	*home_dir;
// 	char	*username = "ael-bako";
// 	struct passwd *pw;

// 	if (!var)
// 		return " ";
// 	if (var[0] == '$')
// 	{
// 		if (strlen(var) == 1)
// 			return "$";
// 		char *env_var = var + 1;
// 		home_dir = getenv(env_var);
// 	}
// 	else if (var[0] == '~')
// 	{strlen(var) > 1)
// 			username = var + 1;
// 		pw = getpwnam(username);
// 		if (!pw)
// 			return var;
// 		home_dir = pw->pw_dir;
// 	}
// 	else
// 		home_dir = var;
// 	return home_dir;
// }

void	fill_node(t_list *node)
{
	token_T* token = (void*)0;
	while (node)
	{
		token = node->content;
		printf("%d, \t%s\n", token->type, token->value);
		node = node->next;
	}
}

int	main(int ac, char **av)
{
	// lexer_T* lexer = init_lexer("echo \"hello  it's  ~0  there\" ~ <how are $RC 'you 'doing? $USER |wc -l >outfile");
	lexer_T* lexer;
	token_T* token = (void*)0;
	t_list	*node, *tmp;
	while ((lexer = init_lexer(readline("minishell$ "))))
	{
		while ((token = lexer_get_next_token(lexer)) != (void*)0)
		{
			tmp = ft_lstnew(token);
			ft_lstadd_back(&node, tmp);
		}
		fill_node(node);
		node = NULL;
	}
	// while (node)
	// {
	// 	token = node->content;
	// 	printf("%d, \t%s\n", token->type, token->value);
	// 	node = node->next;
	// }
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char				*str;
// 	char				*out;
// 	t_prompt			prompt;

// 	prompt = init_prompt(argv, envp);
// 	while (argv && argc)
// 	{
// 		signal(SIGINT, handle_sigint);
// 		signal(SIGQUIT, SIG_IGN);
// 		str = mini_getprompt(prompt);
// 		if (str)
// 			out = readline(str);
// 		else
// 			out = readline("guest@minishell $ ");
// 		free(str);
// 		if (!check_args(out, &prompt))
// 			break ;
// 	}
// 	exit(g_status);
// }
