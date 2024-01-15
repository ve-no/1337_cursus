/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:33:07 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/23 14:45:21 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_scape(char *s, int i)
{
	int	len;

	len = 0;
	while ((s[i] == '<' && s[i - 1] == '<')
		|| (s[i] == '>' && s[i - 1] == '>'))
	{
		i++;
		len++;
	}
	return (len);
}

static int	ft_count_w(char *s, char *set, int count)
{
	int		q[3];

	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	while (s && s[q[2]] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[q[2]]))
		{
			while ((!ft_strchr(set, s[q[2]]) || q[0] || q[1]) && s[q[2]])
			{
				q[0] = (q[0] + (!q[1] && s[q[2]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[q[2]] == '\"')) % 2;
				q[2]++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			q[2]++;
		q[2] += ft_scape(s, q[2]);
	}
	return (count);
}

static char	**ft_fill_tab(char **aux, char *s, char *set, int i[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		i[0] += ft_scape(s, i[0]);
		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_subsplit(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_w((char *)s, set, 0);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (!aux)
		return (NULL);
	aux = ft_fill_tab(aux, (char *)s, set, i);
	aux[nwords] = NULL;
	return (aux);
}
