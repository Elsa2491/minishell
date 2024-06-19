/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:12:11 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_header(void)
{
	ft_printf(2, "\n\e[2m ####################################\e[0m");
	ft_printf(2, "\e[2m####################################\n\n\e[0m");
}

void	ft_print_footer(void)
{
	ft_print_header();
	exit(EXIT_FAILURE);
}

void	ft_print_wrong_param(void)
{
	ft_print_header();
	ft_printf(2, "\033[%dm\e[1m%s\e\033[0m", 31, WARNING);
	ft_printf(2, " It seems something went wrong.\n");
	ft_printf(2, " You must enter only 1 parameter.");
	ft_printf(2, " See the example below:\n");
	ft_printf(2, "\t\033[%dm\e[1m%s\e\033[0m", 32, ARROW);
	ft_printf(2, " \033[%dm./minishell\033[0m ");
	ft_print_footer();
}
