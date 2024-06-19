/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:28:55 by ahayon            #+#    #+#             */
/*   Updated: 2024/02/28 14:58:18 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!len && (!little || !big))
		return (NULL);
	if (ft_strlen(little) == 0)
		return (big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && *little && (i + j) < len)
		{
			if (j + 1 == ft_strlen(little))
				return (&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
