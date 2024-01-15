/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:47:17 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 14:22:02 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alpha(char *cmd)
{
	int		i;

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

int	check_set(char const *set, int s)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrimfree(char *s1, char const *set)
{
	int		len;
	char	*ptr;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	ptr = (char *)s1;
	len = (int)ft_strlen (s1) - 1;
	if (!s1)
		return (NULL);
	while (ptr[len] && check_set(set, ptr[len]))
		len--;
	if (len < 0)
		return (ft_strdup(""));
	while (ptr[i] && check_set(set, ptr[i]))
		i++;
	ptr = ft_substr(s1, i, len - i + 1);
	free(s1);
	return (ptr);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*s3;
	int		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = (char *)malloc(len_s1 + len_s2 + 1);
	if (s3 == NULL)
		return (NULL);
	while (i < len_s1 || i < len_s2)
	{
		if (i < len_s1)
			s3[i] = s1[i];
		if (i < len_s2)
			s3[i + len_s1] = s2[i];
		i++;
	}
	s3[len_s1 + len_s2] = '\0';
	free(s1);
	return (s3);
}

char	*get_variable_from_cmd(char *cmd)
{
	char	**str;
	char	*variable;
	int		i;

	str = ft_split(cmd, '=');
	variable = str[0];
	i = 0;
	while (str[++i])
		free(str[i]);
	free(str);
	return (variable);
}
