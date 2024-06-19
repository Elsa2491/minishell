/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:09:58 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:15:40 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointeur(int fd, unsigned long n)
{
	int		result;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 16)
		return (ft_putchar(fd, symbols[n]));
	else
	{
		result = ft_print_pointeur(fd, n / 16);
		result += ft_print_pointeur(fd, n % 16);
		return (result);
	}
}

int	ft_print_address(int fd, uintptr_t n)
{
	if (n == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	else
	{
		write(fd, "0x", 2);
		return (ft_print_pointeur(fd, n) + 2);
	}
}
