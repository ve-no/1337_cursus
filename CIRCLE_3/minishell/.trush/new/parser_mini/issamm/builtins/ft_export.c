/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:16:22 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/14 17:52:14 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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

char	*get_value_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!str)
		return (NULL);
	int len =  get_char_index(str, '=');
	int test = strlen(str) - len + 2;
	tmp = malloc(sizeof(char) * (test + 1));
	if (!tmp)
		return (NULL);
	while (len < test)
		tmp[++i] = str[++len];
	tmp[i] = 0;
	return (tmp);
}

int	big_len(int s1, int s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}

int    check_alpha(char *cmd)
{
    int    i;

    i = 1;
    while (cmd[i])
    {
        if (ft_isalnum(cmd[i]) || cmd[i] == '_'
            || (cmd[i] == '+' && cmd[i + 1] == '='))
            i++;
        else if (cmd[i] == '=')
            return (1);
        else
            return (0);
    }
    return (1);
}

void bubbleSort(char* environ[], int size)
{
    int i;
	int	j;
	int test = 0;

	i = 0;
	while(i < size - 1)
	{
		j = 0;
		while (j < size -1)
		{
			if (strcmp(environ[j], environ[j + 1]) > 0)
			{
                char* temp = environ[j];
                environ[j] = environ[j + 1];
                environ[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while(environ[i])
	{
		j = 0;
		test = 0;
		printf("declare -x ");
		while (environ[i][j])
		{
			if (environ[i][j] == '=')
			{
				test = 1;
				printf("%c", environ[i][j]);
				printf("\"");
			}
			else
				printf("%c", environ[i][j]);
			j++;
		}
		if (test != 0)
			printf("\"");
		printf("\n");
		i++;
	}
	return ;
}

void	print_export(char **environ)
{
	int i;
	int count;
	char **env_copy = NULL;

	i = 0;
	count = 0;
	while(environ[count])
		count++;
	env_copy = (char**)malloc((count + 1) * sizeof(char*));
	while (i < count)
	{
		 env_copy[i] = strdup(environ[i]);
        if (env_copy[i] == NULL)
		{
            printf("Failed to allocate memory.");
            return;
        }
		i++;
	}
	env_copy[i] = NULL;
	bubbleSort(env_copy, count);
}

void	export_function(t_prompt	*p, char *cmd)
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
	int testp = 0;
	int i;
	i = 1;
	if (strchr(cmd, '='))
		testp = 1;
	str = ft_split(cmd, '=');
	while (str[i])
	{
		value = ft_strjoin(value, str[i]);
		if(str[i + 1])
			value = ft_strjoin(value, "=");
		i++;
	}
	if (!str[1] && testp)
		value = strdup("");
	variable = str[0];
	char *test;
	int iss = 0;
	i = 0;
	while (environ[i] != NULL)
	{
		test = get_variable_name(environ[i]);

		if(variable[strlen(variable) - 1] == '+')
		{
		// khasni nhayad + mn variable w ndir join l value li kant fl value mea l value jdida
			variable = ft_strtrim(variable, "+");
			iss = 1;
		}
		if (strncmp(variable, test, big_len(ft_strlen(variable), ft_strlen(test))) == 0)
		{
			if (value != NULL && iss == 0)
			{
				char *export = malloc(strlen(variable) + strlen(value) + 2); // for '=' w '\n'
				if (!export)
				{
					printf("failed allocatin\n");
					exit(0);
				}
				snprintf(export, strlen(variable) + strlen(value) + 2, "%s=%s", variable, value);
				p->envp[i] = export;
			}
			else if (value != NULL && iss == 1)
			{
				char *old_value = get_value_name(environ[i]);
				char *export = malloc(strlen(variable) + strlen(value) + strlen(old_value) + 2); // for '=' w '\n'
				export = ft_strjoin(test, "=");
				export = ft_strjoin(export, old_value);
				export = ft_strjoin(export, value);

				p->envp[i] = export;
			}
			return ;
		}
		i++;
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

// void export_function(t_prompt *p, char *cmd);

// char *get_value_from_cmd(char *cmd)
// {
//     char **str = ft_split(cmd, '=');
//     char *value = NULL;
//     int i = 1;

//     while (str[i])
//     {
//         value = ft_strjoin(value, str[i]);
//         if (str[i + 1])
//             value = ft_strjoin(value, "=");
//         i++;
//     }

//     if (!str[1] && strchr(cmd, '='))
//         value = strdup("");

//     return value;
// }

// char *get_variable_from_cmd(char *cmd)
// {
//     char **str = ft_split(cmd, '=');
//     char *variable = str[0];
//     if (variable[strlen(variable) - 1] == '+')
//         variable = ft_strtrim(variable, "+");
//     return variable;
// }

// void update_existing_variable(t_prompt *p, char *variable, char *value)
// {
//     char *export;
//     char *test;
//     char *old_value;
//     int iss = 0;
//     int i = 0;
//     char **environ = p->envp;

//     while (environ[i] != NULL)
//     {
//         test = get_variable_name(environ[i]);

//         if (variable[strlen(variable) - 1] == '+')
//         {
//             variable = ft_strtrim(variable, "+");
//             iss = 1;
//         }

//         if (strncmp(variable, test, big_len(ft_strlen(variable), ft_strlen(test))) == 0)
//         {
//             if (value != NULL && iss == 0)
//             {
//                 export = malloc(strlen(variable) + strlen(value) + 2);
//                 if (!export)
//                 {
//                     printf("failed allocation\n");
//                     exit(0);
//                 }
//                 snprintf(export, strlen(variable) + strlen(value) + 2, "%s=%s", variable, value);
//                 p->envp[i] = export;
//             }
//             else if (value != NULL && iss == 1)
//             {
//                 old_value = get_value_name(environ[i]);
//                 export = malloc(strlen(variable) + strlen(value) + strlen(old_value) + 2);
//                 export = ft_strjoin(test, "=");
//                 export = ft_strjoin(export, old_value);
//                 export = ft_strjoin(export, value);

//                 p->envp[i] = export;
//             }
//             return;
//         }

//         i++;
//     }
// }

// void append_new_variable(t_prompt *p, char *variable, char *value)
// {
//     size_t export_length = strlen(variable) + strlen(value) + 2;
//     char *export = malloc(export_length);
//     snprintf(export, export_length, "%s=%s", variable, value);

//     int num_variables = 0;
//     char **environ = p->envp;
//     while (environ[num_variables] != NULL)
//         num_variables++;

//     char **env = malloc((num_variables + 3) * sizeof(char *));
//     int i = -1;
//     while (environ[++i])
//         env[i] = environ[i];

//     env[num_variables] = export;
//     env[num_variables + 1] = NULL;
//     p->envp = env;
// }

// void export_function(t_prompt *p, char *cmd)
// {
//     char *variable = get_variable_from_cmd(cmd);
//     char *value = get_value_from_cmd(cmd);

//     update_existing_variable(p, variable, value);
//     append_new_variable(p, variable, value);
// }


void ft_export(t_prompt *p)
{
	t_list *list;
	t_mini	*mini;

	list =p->cmds;
	mini = list->content;
	int i = 1;

	if(mini->full_cmd[1] == NULL)
		print_export(p->envp);
	else
	{
		while(mini->full_cmd[i])
		{
            if (!ft_isalpha(mini->full_cmd[i][0]) && mini->full_cmd[i][0] != '_')
                printf("not a valid identifier\n");
            else if (!check_alpha(mini->full_cmd[i]))
                printf("not a valid identifier\n");
			else
				export_function(p, mini->full_cmd[i]);
			i++;
		}
	}
}
