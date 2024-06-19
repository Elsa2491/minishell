/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:42:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/17 22:11:03 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_echo_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		if (str[i] == 'n')
		{
			while (str[i])
			{
				if (str[i] != 'n')
					return (false);
				i++;
			}
			return (true);
		}
		else
			return (false);
	}
	else
		return (false);
}

void	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!*args)
		return ;
	while (args[i] && ft_is_echo_n(args[i]))
	{
		i++;
		n = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && ft_strcmp(args[i], "\0") != 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
	ft_exit_code(0, ADD);
}
