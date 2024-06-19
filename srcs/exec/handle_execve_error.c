/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execve_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:10:38 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/16 23:40:51 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_execve_error(t_data *data, t_cmds *cmds)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmds->right_path);
	free(cmds->right_path);
	while (cmds && cmds != NULL)
	{
		ft_free_tab(cmds->cmd_path);
		cmds->cmd_path = NULL;
		ft_free_tab(data->mini_env);
		data->mini_env = NULL;
		cmds = cmds->next;
	}
	ft_clean_all(data);
	ft_exit_code(1, ADD);
	exit (1);
}
