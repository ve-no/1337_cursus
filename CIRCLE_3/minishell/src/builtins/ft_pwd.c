/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:39:02 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 18:55:36 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char *pwd)
{
	printf("%s\n", pwd);
	return (0);
}

void	failed_fork(void)
{
	printf("minishell: fork: Resource temporarily unavailable\n");
	exit(1);
}

char	*get_value(char *str, char *stre, char *value)
{
	char	*tmp;

	tmp = ft_strjoin("", str);
	value = ft_strdup(tmp);
	free(tmp);
	if (stre)
	{
		tmp = ft_strjoin(value, "=");
		value = tmp;
		free(tmp);
	}
	return (value);
}

char	*value_exist_without_plus(char *variable, char *value,
			char *environ, char *envp)
{
	char	*export;

	export = malloc(ft_strlen(variable) + ft_strlen(value) + 2);
	if (!export)
		failed_allocation();
	my_snprintf(export, ft_strlen(variable)
		+ ft_strlen(value) + 2, "%s=%s", variable, value);
	free(environ);
	envp = export;
	return (envp);
}

char	*value_exist_with_plus(char *environ, char *value,
			char *variable, char *envp)
{
	char	*old_value;
	char	*export;

	old_value = get_value_name(environ);
	export = malloc(ft_strlen(variable) + ft_strlen(value)
			+ ft_strlen(old_value) + 2);
	if (!export)
		failed_allocation();
	my_snprintf(export, ft_strlen(variable) + ft_strlen(value)
		+ ft_strlen(old_value)
		+ 2, "%s=%s%s", variable, old_value, value);
	free(old_value);
	free(environ);
	envp = export;
	return (envp);
}
