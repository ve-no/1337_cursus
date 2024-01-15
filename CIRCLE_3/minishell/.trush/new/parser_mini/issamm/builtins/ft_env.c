/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:57:21 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/14 14:21:44 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	ft_env(t_prompt *p)
{
	int	i;

	i = -1;
	if (!p->envp)
		return ;
	while (p->envp[++i] != NULL)
	{
		if (ft_strchr(p->envp[i], '='))
			printf("%s\n", p->envp[i]);
	}
}
