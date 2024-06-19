/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:59:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/02/28 14:57:32 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (!c)
		return (s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			j = i;
		}
		i++;
	}
	if (j == -1)
	{
		return (NULL);
	}
	return ((char *)&(s[j]));
}
