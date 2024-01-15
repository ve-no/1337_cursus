/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsubsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:33:07 by ael-bako          #+#    #+#             */
/*   Updated: 2023/06/14 16:52:42 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_count_words(char *s, char *set, int count)
{
	int		q[3];

	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	while (s && s[q[2]] != '\0')
	{
		// if (!((s[q[2]] == '<' && s[q[2] - 1] == '<')
		// 		|| (s[q[2]] == '>' && s[q[2] - 1] == '>')))
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
		while ((s[q[2]] == '<' && s[q[2] - 1] == '<')
			|| (s[q[2]] == '>' && s[q[2] - 1] == '>'))
			q[2]++;
	}
	return (count);
}

static char	**ft_fill_array(char **aux, char *s, char *set, int i[3])
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
		while ((s[i[0]] == '<' && s[i[0] - 1] == '<')
			|| (s[i[0]] == '>' && s[i[0] - 1] == '>'))
			i[0]++;
		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_cmdsubsplit(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words((char *)s, set, 0);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (!aux)
		return (NULL);
	aux = ft_fill_array(aux, (char *)s, set, i);
	aux[nwords] = NULL;
	return (aux);
}

// int main(int ac, char **av)
// {
// 	char	*s = "<<  >>";
// 	char **str = ft_cmdsubsplit(av[1], "<|>");
// 	int i = -1;
// 	while (str[++i])
// 		printf(":%s:\n", str[i]);
// }
