
#include "parser.h"


char	*mini_env(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = strlen(var);
	while (!strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, strlen(envp[i])));
		i++;
	}
	return (NULL);
}

int ft_cd(t_prompt	*p)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;
	char	**str;
	int		i;

    path = NULL;
	str = ((t_mini *)p->cmds->content)->full_cmd;
    oldpwd = ft_strjoin(ft_strdup("OLDPWD="), getcwd(NULL, 0));
    if (str[1] == NULL)
        path = mini_env("HOME", p->envp, 4);
    else
        path = str[1];
    chdir(path);
	pwd = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
	i = -1;
	while (p->envp[++i])
	{
		if (!(ft_strncmp(p->envp[i], "PWD=", 4)))
			ft_replace_in(&p->envp, pwd, i);
		else if (!(ft_strncmp(p->envp[i], "OLDPWD=", 7)))
			ft_replace_in(&p->envp, pwd, i);
	}
	i = -1;
	while (str[++i])
	{
		printf("%s\n", str[i]);
	}
    printf("%s\n", pwd);
    printf("%s\n", oldpwd);
}

// eandi 2 cas wahd fih l path w wahd bla path
int main(int ac, char **av, char **env)
{
    char    *path;
    char    *oldpwd;
	char	*pwd;

    path = NULL;
    oldpwd = ft_strjoin(ft_strdup("OLDPWD="), getcwd(NULL, 0));   // Here dir equals the home environment.
    if (av[1] == NULL)
        path = mini_env("HOME", env, 4);
    else if(ac == 2)
        path =    av[1];
    chdir(path);
	pwd = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));

    printf("%s\n", pwd);
    printf("%s\n", oldpwd);
    return 0;
}

// int main(int ac, char **av, char **env)
// {
// 	char	**str = ft_dup_matrix(env);
// 	int		i = -1;
// 	char	*s = "PWD=hhhhh";

// 	while (str[++i])
// 	{
// 		if (!(ft_strncmp(str[i], "PWD=", 4)))
// 			ft_replace_in(&str, s, i);
// 	}
// 	i = -1;
// 	while (str[++i])
// 	{
// 		printf("%s\n", str[i]);
// 	}

// }
