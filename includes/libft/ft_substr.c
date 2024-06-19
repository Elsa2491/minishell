/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:53:50 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/10 19:11:32 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char *s, size_t start, size_t len)
{
	char			*subs;
	size_t			i;
	size_t			s_size;

	i = 0;
	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (start >= s_size)
		len = 0;
	if (len > s_size - start)
		len = s_size - start;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	while (i < len)
	{
		subs[i] = s[start];
		start++;
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
