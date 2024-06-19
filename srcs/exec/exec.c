/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/19 14:36:16 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_init_exec(t_cmds *cmds)
{
	while (cmds != NULL)
	{
		cmds->cmd_count = ft_lstsize_cmd(cmds);
		cmds = cmds->next;
	}
}

int	ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	t_redir	*head;
	t_cmds	*head_cmds;

	head_cmds = cmds;
	while (cmds != NULL)
	{
		head = cmds->redir;
		while (head != NULL)
		{
			if (head->type == 2)
			{
				if (!ft_exec_here_doc(data, cmds, head, head_cmds))
					return (-2);
			}
			head = head->next;
		}
		cmds = cmds->next;
	}
	return (-1);
}

int	ft_exec(t_data *data, t_cmds *cmds)
{
	if (!cmds)
		return (ft_exit_code(0, GET));
	ft_init_exec(cmds);
	ft_is_max_here_doc_nb_reached(data, cmds);
	if (ft_handle_here_doc(data, cmds) == -2)
		return (ft_exit_code(0, GET));
	if (cmds->cmd_count == 1)
	{
		ft_is_only_one_cmd(data, cmds);
		ft_free_tab(cmds->cmd_path);
		ft_free_tab(data->mini_env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		ft_handle_pipes(data, cmds);
	}
	ft_close_hd_in_fork(cmds, NULL);
	return (ft_exit_code(0, GET));
}
