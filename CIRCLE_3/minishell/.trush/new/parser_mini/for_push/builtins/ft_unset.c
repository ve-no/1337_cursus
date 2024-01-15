/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:05:38 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/09 12:21:40 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void unset_variable(const char *variable, char **environ)
{
    int i, j;
    int len = strlen(variable);

	i = 0;
	while (environ[i] != NULL)
	{
		 if (strncmp(variable, environ[i], len) == 0 && environ[i][len] == '=')
		  {
			j = i;
			while(environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
            i--;
        }
		i++;
    }
}

int main(int argc, char *argv[], char **env)
{
	int i = 1;

    if (argc < 2) {
        printf("unset: not enough arguments\n");
        return 1;
    }
	while(i < argc)
	{
		unset_variable(argv[i], env);
		i++;
	}
    return 0;
}
