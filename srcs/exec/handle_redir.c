/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/17 18:36:33 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_red_out_and_append(t_data *data, t_cmds *cmds, t_redir *tmp)
{
	if (tmp->type == APPEND || tmp->type == RED_OUT)
		ft_handle_output_and_append(data, cmds, tmp);
}

int	ft_handle_redir(t_data *data, t_cmds *cmds)
{
	t_redir	*tmp;
	int		count;

	tmp = cmds->redir;
	count = 0;
	while (tmp != NULL)
	{
		ft_red_out_and_append(data, cmds, tmp);
		if (tmp->type == HEREDOC)
			ft_read_here_doc(data, cmds, &count);
		if (tmp->type == RED_IN)
		{
			if (ft_is_a_built_in(cmds->cmd) || !cmds->cmd)
			{
				if (access(tmp->path, F_OK | R_OK | W_OK) != 0)
					return (ft_handle_built_in_error(data, tmp));
			}
			else
				ft_handle_input(data, cmds, tmp);
		}
		tmp = tmp->next;
	}
	ft_close_hd_in_fork(data->cmd_list, NULL);
	ft_clear_redirlst(&cmds->redir, &ft_free_ptr);
	return (ft_exit_code(0, GET), 1);
}
