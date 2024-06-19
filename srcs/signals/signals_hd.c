/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:37:07 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/18 00:56:43 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_c_heredoc(int sig)
{
	(void)sig;
	ft_putchar(1, '\n');
	close(0);
	g_sig_exit = 4;
	ft_exit_code(130, ADD);
}

void	ft_handle_sig_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_ctrl_c_heredoc);
}

bool	ft_quit_ctrl_c(int *pid, t_data *data, t_cmds *head_cmds, t_cmds *cmds)
{
	waitpid(*pid, pid, 0);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
	{
		ft_close_hd_in_fork(head_cmds, cmds);
		if (close(cmds->hd_read) == -1)
			ft_handle_close_error(data, cmds);
		if (close(cmds->hd_write) == -1)
			ft_handle_close_error(data, cmds);
		return (ft_exit_code(130, ADD), true);
	}
	return (false);
}

void	ft_quit_in_fork(t_data *data, t_cmds *cmds, char *line, char *delimiter)
{
	free(line);
	free(delimiter);
	if (close(cmds->hd_write) == -1)
		ft_handle_close_error(data, cmds);
	ft_clean_all(data);
	exit(2);
}
