/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/17 20:15:38 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_absolute_path(t_data *data, t_cmds *cmds)
{
	char	*tmp;

	tmp = ft_strjoin_exec(data, cmds->cmd, "/");
	if (access(tmp, F_OK) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmds->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(tmp);
		ft_free_tab(cmds->args);
		ft_free_tab(cmds->cmd_path);
		ft_free_tab(data->mini_env);
		exit (126);
	}
	free(tmp);
	return (ft_strdup_exec(data, cmds->cmd));
}

static int	ft_is_a_directory(t_data *data, char *argv)
{
	char	*tmp;

	tmp = ft_strjoin_exec(data, argv, "/");
	if (access(tmp, F_OK) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static char	*ft_handle_path(t_data *data, t_cmds *cmds, char *cmd, int i)
{
	char	*tmp;
	char	*tmp2;

	while (cmds->cmd_path && cmds->cmd_path[i])
	{
		tmp = ft_strjoin_exec(data, cmds->cmd_path[i++], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!tmp2)
			(ft_exit_code(300, ADD), ft_exit_if_malloc(data));
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
				return (tmp2);
			else
				ft_handle_rights(data, cmds, cmd, tmp2);
		}
		free(tmp2);
	}
	ft_free(data, cmds, cmd, "command not found\n");
	exit (ft_exit_code(127, ADD));
}

char	*ft_get_cmd_path(t_data *data, t_cmds *cmds, char *cmd)
{
	int	i;

	i = 0;
	if (access(cmd, F_OK) == -1 && ft_strchr(cmd, '/'))
		ft_handle_no_file_or_dir(data, cmds, cmd);
	if (access(cmd, F_OK) == 0 && (ft_strchr(cmd, '/')
			|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
			|| (cmd[0] == '.' && cmd[1] == '/')))
	{
		if (ft_is_a_directory(data, cmd))
			ft_handle_directory(data, cmds, cmd);
		if (access(cmd, X_OK) != 0)
			ft_handle_rights(data, cmds, cmd, NULL);
		else
			return (ft_get_absolute_path(data, cmds));
		return (NULL);
	}
	return (ft_handle_path(data, cmds, cmd, i));
}
