/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:39:02 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/13 20:04:31 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	ft_pwd(char *pwd, char **cmds)
{
	if(ft_strlen_2(cmds) == 1)
		printf("%s\n", pwd);
	else
		printf("pwd: too many arguments\n");
}
