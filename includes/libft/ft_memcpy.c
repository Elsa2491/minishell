/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:25:01 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/23 19:26:48 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*str1;
	const unsigned char	*str2;

	if (!dest && !src)
		return (NULL);
	str1 = dest;
	str2 = src;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (str1);
}

/*#include <stdio.h>

int	main()
{
	char	str1[] = "appaeewfwe";
	char	str2[] = "hello";
	char	str3[] = "appa";

	printf("%s\n", (char*)ft_memcpy(str1, str2, 45));
}*/
