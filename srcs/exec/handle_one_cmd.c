/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_one_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/17 18:41:26 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_one_no_built_in_cmd(t_data *data, t_cmds *cmds)
{
	ft_handle_sig_child();
	if (cmds->cmd[0] == '\0')
	{
		ft_putstr_fd("minishell$: command not found\n", 2);
		return (ft_exit_code(127, ADD));
	}
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
		ft_exec_cmds(data, cmds);
	ft_add_pid(data, cmds->pid);
	if (cmds->hd_read > 0 && close(cmds->hd_read) == -1)
		ft_handle_close_error(data, cmds);
	return (ft_exit_code(0, GET));
}

/*
 * Pourquoi ce if (cmds->infile != -1) ?
 *
 * On a set cmds->infile a 0 au debut
 * S'il est a -1 c'est qu'il y a eu une erreur, 
 * qu'on n'a pas pu l'ouvrir
 * S'il est au contraire il est != -1,
 * c'est que tout s'est bien passe, qu'on a un infile
 * Et la deux options :
 * 	1 - la commande est exit, donc il close stdin/stdout
 * 		qu'on avait ouvert avant de quitter
 * 	2 - la commande n'est pas exit, on l'execute
 */
int	ft_only_one_built_in(t_data *data, t_cmds *cmds)
{
	ft_dup_stdin_stdout(data, cmds);
	if (ft_handle_redir(data, cmds)
		&& cmds->infile != -1 && cmds->outfile != -1)
		ft_exec_built_in(data, cmds);
	ft_dup2_and_close_stdin_stdout(data, cmds);
	return (ft_exit_code(0, GET));
}

int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds)
{
	ft_get_path(data, cmds);
	if (!ft_strcmp(cmds->cmd, ":") || !ft_strcmp(cmds->cmd, "!"))
	{
		ft_putstr_fd("", 1);
		if (!ft_strcmp(cmds->cmd, "!"))
			return (ft_exit_code(1, ADD));
		return (ft_exit_code(0, GET));
	}
	if (!cmds->args)
	{
		ft_dup_stdin_stdout(data, cmds);
		ft_handle_redir(data, cmds);
		ft_dup2_and_close_stdin_stdout(data, cmds);
		return (ft_exit_code(0, GET));
	}
	if (ft_is_a_built_in(cmds->cmd))
		return (ft_only_one_built_in(data, cmds));
	else
		return (ft_one_no_built_in_cmd(data, cmds));
}
