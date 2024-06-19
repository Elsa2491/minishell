/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:57:30 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/23 18:59:54 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*source;

	dst = dest;
	source = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dst < source)
		ft_memcpy(dst, source, n);
	else
	{
		while (n > 0)
		{
			dst[n - 1] = source[n - 1];
			n--;
		}
	}
	return (dst);
}
