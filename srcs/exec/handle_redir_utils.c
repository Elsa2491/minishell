/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/17 18:46:24 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_read_here_doc(t_data *data, t_cmds *cmds, int *count)
{
	*count += 1;
	if (*count == cmds->here_doc_count)
	{
		if (dup2(cmds->hd_read, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->hd_read) == -1)
			ft_handle_close_error(data, cmds);
	}
}

void	ft_handle_output_and_append(t_data *data, t_cmds *cmds, t_redir *redir)
{
	int	flag;

	if (redir->type == APPEND)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	cmds->outfile = open(redir->path, O_WRONLY | O_CREAT | flag, 0755);
	if (cmds->outfile == -1)
		ft_handle_file_error(data, cmds, redir);
	else
	{
		if (dup2(cmds->outfile, 1) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->outfile) == -1)
			ft_handle_close_error(data, cmds);
	}
}

static void	ft_open_input(t_data *data, t_cmds *cmds, t_redir *tmp)
{
	cmds->infile = open(tmp->path, O_RDONLY, 0755);
	if (cmds->infile == -1)
		ft_handle_file_error(data, cmds, tmp);
	else
	{
		if (dup2(cmds->infile, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->infile) == -1)
			ft_handle_close_error(data, cmds);
	}
}

void	ft_handle_input(t_data *data, t_cmds *cmds, t_redir *tmp)
{
	if (access(tmp->path, F_OK) == 0)
		ft_open_input(data, cmds, tmp);
	else
		ft_handle_file_error(data, cmds, tmp);
}

int	ft_handle_built_in_error(t_data *data, t_redir *tmp)
{
	ft_close_hd_in_fork(data->cmd_list, NULL);
	ft_putstr_fd("minishell: ", 2);
	perror(tmp->path);
	ft_exit_code(1, ADD);
	return (0);
}
