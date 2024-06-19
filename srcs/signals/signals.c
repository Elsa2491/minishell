/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:41:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/18 00:53:55 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cc_handler(int sig)
{
	(void)sig;
	ft_putchar(2, '\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_exit = 2;
	ft_exit_code(130, ADD);
}

void	ft_cc_blocking(int sig)
{
	(void)sig;
	g_sig_exit = 2;
	ft_exit_code(130, ADD);
}

void	ft_bckslsh_handler(int sig)
{
	(void)sig;
	g_sig_exit = 3;
	ft_exit_code(131, ADD);
}

void	ft_handle_signal(void)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_cc_handler);
}

void	ft_handle_sig_child(void)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, &ft_bckslsh_handler);
	signal(SIGINT, &ft_cc_blocking);
}
