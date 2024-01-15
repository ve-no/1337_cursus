/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:54:54 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/23 14:39:19 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*exp_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0 || \
			str[i - 1] != '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (exp_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

static char	*substr_var(char *str, int i, t_prompt *prompt)
{
	char	*aux;
	int		p;
	char	*path;
	char	*var;

	p = ft_strchars_i(&str[i], "\"\'$?- ") + (ft_strchr("$?", str[i]) != 0);
	if (p == -1)
		p = ft_strlen(&str[i]);
	aux = ft_substr(str, 0, i - 1);
	var = mini_env(&str[i], prompt->envp, \
		ft_strchars_i(&str[i], "-\"\'$ "));
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &str[i + p]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

char	*exp_va(char *prev, char *str, int i, t_prompt *prompt)
{
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	if (!ft_strncmp(prev, "<<", 3))
		return (str);
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "- ") && !quotes[1]) || \
			(ft_strchars_i(&str[i + 1], "-\"") && quotes[1])))
			return (exp_va(prev, substr_var(str, ++i, prompt),
					-1, prompt));
	}
	return (str);
}
