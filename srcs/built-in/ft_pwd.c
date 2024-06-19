/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:28:40 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/09 14:46:10 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmds *cmds)
{
	char	*working_dir;

	(void)cmds;
	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory", 2);
		ft_exit_code(1, ADD);
	}
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd("\n", 1);
	free(working_dir);
	working_dir = NULL;
	return (0);
}
