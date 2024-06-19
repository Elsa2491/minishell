/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:32:41 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/30 12:40:44 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_digits(int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		c = 1;
	while (n != 0)
	{
		n /= 10;
		c += 1;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		res;
	char	*str;

	nb = n;
	res = count_digits(nb);
	str = (char *)malloc(sizeof(char) * res + 1);
	if (!str)
		return (NULL);
	str[res] = '\0';
	if (n < 0)
	{
		nb *= -1;
	}
	while (res > 0)
	{
		str[res - 1] = nb % 10 + '0';
		nb /= 10;
		res--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/*
int	main()
{
	printf("%s\n", ft_itoa(-879));
*/
