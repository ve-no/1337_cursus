/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:16:22 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 18:50:07 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_from_cmd(char *cmd)
{
	char	**str;
	char	*value;
	int		i;

	str = ft_split(cmd, '=');
	value = NULL;
	i = 0;
	while (str[++i])
		value = get_value(str[i], str[i + 1], value);
	i = 0;
	if (ft_strchr(cmd, '='))
		i = 1;
	if (!str[1] && i)
		value = ft_strdup("");
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (value);
}

int	update_existing_variable(t_prompt *p, char *variable, char *value, int plus)
{
	char	*test;
	int		i;
	char	**environ;

	i = 0;
	environ = p->envp;
	while (environ[i] != NULL)
	{
		test = get_variable_name(environ[i]);
		if (ft_strncmp(variable, test, big_len(ft_strlen(variable),
					ft_strlen(test))) == 0)
		{
			if (value != NULL && plus == 0)
				p->envp[i] = value_exist_without_plus(variable, value,
						environ[i], p->envp[i]);
			else if (value != NULL && plus == 1)
				p->envp[i] = value_exist_with_plus(environ[i], value,
						variable, p->envp[i]);
			free(test);
			return (1);
		}
		free(test);
		i++;
	}
	return (0);
}

int	check_if_already_present(t_prompt *p, char *variable)
{
	int		i;
	char	*test;

	i = 0;
	while (p->envp[i])
	{
		test = get_variable_name(p->envp[i]);
		if (!ft_strncmp(variable, test, big_len(ft_strlen(variable),
					ft_strlen(test))))
		{
			free(test);
			return (1);
		}
		i++;
		free(test);
	}
	return (0);
}

void	export_function(t_prompt *p, char *cmd)
{
	char		*variable;
	char		*value;
	int			withplus;

	withplus = 0;
	variable = get_variable_from_cmd(cmd);
	if (ft_strchr(variable, '+'))
	{
		variable = ft_strtrimfree(variable, "+");
		withplus = 1;
	}
	value = get_value_from_cmd(cmd);
	if (check_if_already_present(p, variable))
		update_existing_variable(p, variable, value, withplus);
	else
		append_new_variable(p, variable, value);
	free(variable);
	free(value);
}

void	ft_export(t_prompt *p, t_mini *mini)
{
	int	i;

	i = 1;
	if (mini->full_cmd[1] == NULL)
		print_export(p->envp);
	else
	{
		while (mini->full_cmd[i])
		{
			if (!ft_isalpha(mini->full_cmd[i][0]) &&
				mini->full_cmd[i][0] != '_')
				printf("not a valid identifier\n");
			else if (!check_alpha(mini->full_cmd[i]))
				printf("not a valid identifier\n");
			else
				export_function(p, mini->full_cmd[i]);
			i++;
		}
	}
}
