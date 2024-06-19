/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/17 18:54:57 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exit_errors(t_data *data, t_cmds *cmds, int code, char *str)
{
	(void)data;
	(void)cmds;
	if (code == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_exit_code(2, ADD);
	}
	else if (code == 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_exit_code(1, ADD);
	}
}

static bool	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ft_get_status(char *nb)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (nb[i] && (nb[i] == 32 || nb[i] == 9))
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			sign = -1;
		i++;
	}
	while (nb[i])
	{
		res = (res * 10) + (nb[i] - '0');
		if ((sign == 1 && res > LLONG_MAX)
			|| (sign == -1 && res - 1 > LLONG_MAX))
			return (-1);
		i++;
	}
	return ((res * sign) % 256);
}

static void	ft_exit_bis(t_data *data, t_cmds *cmd)
{
	if (!cmd->next && !cmd->prev)
		ft_putstr_fd("exit\n", 1);
	if (cmd->args[1] && !ft_is_number(cmd->args[1]))
	{
		ft_exit_errors(data, cmd, 1, cmd->args[1]);
		if (cmd->prev || cmd->next)
			return ;
	}
	else if (cmd->args && cmd->args[1]
		&& ft_is_number(cmd->args[1]) && cmd->args[2])
	{
		ft_exit_errors(data, cmd, 2, cmd->args[1]);
		return ;
	}
	else if (cmd->args[1] && ft_is_number(cmd->args[1]))
	{
		if (ft_get_status(cmd->args[1]) == -1)
			ft_exit_errors(data, cmd, 1, cmd->args[1]);
		else
			ft_exit_code(ft_get_status(cmd->args[1]), ADD);
	}
	ft_clean_exit(data, cmd);
	exit (ft_exit_code(0, GET));
}

void	ft_exit(t_data *data, t_cmds *cmds)
{
	if (!cmds->next && !cmds->prev)
	{
		if (cmds->args[1] && ft_is_number(cmds->args[1]))
		{
			if (!cmds->args[2])
				ft_dup2_and_close_stdin_stdout(data, cmds);
			ft_exit_bis(data, cmds);
		}	
		else
		{
			ft_dup2_and_close_stdin_stdout(data, cmds);
			ft_exit_bis(data, cmds);
		}
	}
	else
		ft_exit_bis(data, cmds);
}
