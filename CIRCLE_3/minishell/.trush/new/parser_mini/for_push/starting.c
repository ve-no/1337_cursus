/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:34:23 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/06/05 21:37:46 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*ptr;

	count = 0;
	if (lst == NULL)
		return (0);
	ptr = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

int main()
{
	int i;

	i = 0;
	int nodes = ft_lstsize();
	while ()
}
