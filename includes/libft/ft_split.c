/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:23:25 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/09 14:38:11 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_nstr(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
			n++;
		while (s[i] != c && s[i])
			i++;
		if (s[i])
			i++;
	}
	return (n);
}

static void	*ft_free(char **d)
{
	int	i;

	i = 0;
	while (d[i])
		free(d[i++]);
	free(d);
	return (0x0);
}

size_t	ft_strlenc(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	int		nstr;
	int		i;
	char	**d;

	if (!s)
		return (0x0);
	nstr = ft_nstr(s, c);
	d = malloc(sizeof(char *) * (nstr + 1));
	if (!d)
		return (0x0);
	d[nstr] = 0;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			d[i] = ft_substr(s, 0, ft_strlenc(s, c));
			if (!d[i++])
				return (ft_free(d));
			s += ft_strlenc(s, c);
		}
		else
			s++;
	}
	return (d);
}
