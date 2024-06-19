/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:26:54 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/25 14:40:12 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastelem;

	if (!lst || !new)
		return ;
	lastelem = ft_lstlast(*lst);
	if (lastelem == NULL)
		*lst = new;
	else
		lastelem->next = new;
}
