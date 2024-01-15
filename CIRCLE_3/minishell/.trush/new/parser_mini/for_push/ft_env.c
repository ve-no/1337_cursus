/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:57:21 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/24 16:25:28 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

void	ft_env(char **env)
{
	int i ;
	char **str;
	str = ft_dup_matrix(env);
	i = 0;
	if ()
	while(str[i] != NULL)
		printf("%s\n",str[++i]);
}

int main(int ac, char **av, char **env)
{
	ft_env(env);
}
