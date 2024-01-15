/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:50:11 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/23 18:49:51 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(char **environ, int test)
{
	int	i;
	int	j;

	i = -1;
	while (environ[++i])
	{
		j = 0;
		test = 0;
		printf("declare -x ");
		while (environ[i][j])
		{
			if (environ[i][j] == '=')
			{
				test = 1;
				printf("%c\"", environ[i][j]);
			}
			else
				printf("%c", environ[i][j]);
			j++;
		}
		if (test != 0)
			printf("\"");
		printf("\n");
	}
	free(environ);
}

void	bubble_sort(char *environ[], int size)
{
	int		i;
	int		j;
	int		test;
	char	*temp;

	i = 0;
	test = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size -1)
		{
			if (ft_strcmp(environ[j], environ[j + 1]) > 0)
			{
				temp = environ[j];
				environ[j] = environ[j + 1];
				environ[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	print(environ, test);
	return ;
}

void	print_export(char **environ)
{
	int		i;
	int		count;
	char	**env_copy;

	i = 0;
	env_copy = NULL;
	count = 0;
	while (environ[count])
		count++;
	env_copy = (char **) malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		env_copy[i] = environ[i];
		if (env_copy[i] == NULL)
		{
			printf("Failed to allocate memory.");
			return ;
		}
		i++;
	}
	env_copy[i] = NULL;
	bubble_sort(env_copy, count);
}

int	big_len(int s1, int s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}

void	failed_allocation(void)
{
	printf("failed allocation\n");
	exit(0);
}
