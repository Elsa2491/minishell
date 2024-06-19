/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:39:29 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/26 13:52:44 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*newel;

	newel = malloc(sizeof(t_list));
	if (!newel)
		return (NULL);
	newel->content = content;
	newel->next = NULL;
	return (newel);
}
