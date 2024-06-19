/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:01:39 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:16:19 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

int	ft_putchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
	{
		ft_putchar(fd, str[i]);
		i += 1;
	}
	return (i);
}

int	ft_print_digit(int fd, long n, int base, char c)
{
	int		result;
	char	*symbols;

	result = 0;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		ft_putchar(fd, '-');
		n *= -1;
		return (ft_print_digit(fd, n, base, c) + 1);
	}
	if (n < base)
	{
		if (c == 'X')
		{
			symbols = "0123456789ABCDEF";
			return (ft_putchar(fd, symbols[n]));
		}
		return (ft_putchar(fd, symbols[n]));
	}
	else
	{
		result = ft_print_digit(fd, n / base, base, c);
		return (result += ft_print_digit(fd, n % base, base, c));
	}
}

int	ft_print_format(int fd, char c, va_list ap)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_putchar(fd, va_arg(ap, int));
	if (c == 's')
		i += ft_putstr(fd, va_arg(ap, char *));
	if (c == 'd' || c == 'i')
		i += ft_print_digit(fd, va_arg(ap, int), 10, c);
	if (c == 'u')
		i += ft_print_digit(fd, va_arg(ap, unsigned int), 10, c);
	if (c == 'x' || c == 'X')
		i += ft_print_digit(fd, va_arg(ap, unsigned int), 16, c);
	if (c == 'p')
		i += ft_print_address(fd, va_arg(ap, uintptr_t));
	if (c == '%')
		i += write(fd, "%%", 1);
	return (i);
}

int	ft_printf(int fd, const char *last, ...)
{
	int		i;
	int		result;
	va_list	ap;

	i = 0;
	result = 0;
	va_start(ap, last);
	if (!last)
		return (-1);
	while (last[i] != '\0')
	{
		if (last[i] == '%')
		{
			last += 1;
			result += ft_print_format(fd, *last, ap);
		}
		else
			result += write(fd, &last[i], 1);
		last += 1;
	}
	va_end(ap);
	return (result);
}
