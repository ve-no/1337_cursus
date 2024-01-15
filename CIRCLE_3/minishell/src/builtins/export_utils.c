/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:44:04 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 18:54:44 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index(char *str, char c)
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
	int		len;

	i = -1;
	len = get_index(str, '=');
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
	int		len;
	int		test;

	i = -1;
	if (!str)
		return (NULL);
	len = get_index(str, '=');
	test = ft_strlen(str) - len + 2;
	tmp = malloc(sizeof(char) * (test + 1));
	if (!tmp)
		return (NULL);
	while (len < test)
		tmp[++i] = str[++len];
	tmp[i] = 0;
	return (tmp);
}

void	value_exist(char *variable, char *value, char **environ, t_prompt *p)
{
	char		**env;
	size_t		export_length;
	char		*export;
	int			num_variables;

	export_length = ft_strlen(variable) + ft_strlen(value) + 2;
	export = malloc(export_length);
	my_snprintf(export, export_length, "%s=%s", variable, value);
	num_variables = 0;
	while (environ[num_variables] != NULL)
		num_variables++;
	env = malloc((num_variables + 2) * sizeof(char *));
	p->i = -1;
	while (environ[++p->i])
		env[p->i] = ft_strdup(environ[p->i]);
	env[num_variables] = export;
	env[num_variables + 1] = NULL;
	p->i = -1;
	while (p->i < num_variables)
		free(environ[++p->i]);
	free(environ);
	p->envp = env;
}

void	append_new_variable(t_prompt *p, char *variable, char *value)
{
	char	**environ;
	int		i;
	char	**env;
	int		num_variables;

	environ = p->envp;
	if (value != NULL)
		value_exist(variable, value, environ, p);
	else
	{
		num_variables = 0;
		while (environ[num_variables] != NULL)
			num_variables++;
		env = malloc((num_variables + 2) * sizeof(char *));
		i = -1;
		while (environ[++i])
			env[i] = ft_strdup(environ[i]);
		env[num_variables] = ft_strdup(variable);
		env[num_variables + 1] = NULL;
		i = -1;
		while (i < num_variables)
			free(environ[++i]);
		free(environ);
		p->envp = env;
	}
}
