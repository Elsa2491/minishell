/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/16 22:31:40 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_swap_pipes(t_data *data, t_cmds *cmds)
{
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
	if (close(cmds->prev_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
	if (cmds->next)
	{
		cmds->next->prev_pipe[0] = cmds->curr_pipe[0];
		cmds->next->prev_pipe[1] = cmds->curr_pipe[1];
	}
	ft_free_tab(cmds->cmd_path);
	ft_free_tab(data->mini_env);
}

static void	ft_fork_in_pipes(t_data *data, t_cmds *cmds)
{
	ft_handle_sig_child();
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
		ft_handle_processes(data, cmds);
	ft_add_pid(data, cmds->pid);
}

void	ft_handle_pipes(t_data *data, t_cmds *cmds)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (tmp != NULL)
	{
		ft_get_path(data, tmp);
		if (pipe(tmp->curr_pipe) == -1)
			ft_handle_pipe_error(data, tmp);
		ft_fork_in_pipes(data, tmp);
		ft_swap_pipes(data, tmp);
		tmp = tmp->next;
	}
	cmds->i = 0;
	while (cmds->i++ < cmds->cmd_count)
	{
		ft_close_processes(cmds);
		ft_add_pid(data, cmds->pid);
	}
	ft_handle_sig_child();
}
