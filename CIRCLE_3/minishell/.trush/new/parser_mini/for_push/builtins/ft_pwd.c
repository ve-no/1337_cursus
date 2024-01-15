/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:39:02 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/11 14:24:17 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	ft_pwd(void)
{
	char*	retptr = getcwd(NULL, 1024);

	if (retptr == NULL)
	{
		printf("Failed \n");
		if (errno == ERANGE)
			printf("Max buffer lenght\n");
		else if (errno == ENOMEM)
			printf("Memory cannot be allocated for path\n");
	}
	else
		printf("%s\n", retptr);
}
