/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:44:24 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/14 13:40:19 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit_code(int exit_code, int mode)
{
	static int	code = 0;

	if (mode == ADD)
		code = exit_code;
	if (mode == GET)
		return (code);
	return (code);
}

int	ft_expand_code(int expand_code, int mode)
{
	static int	code = 0;

	if (mode == ADD)
		code = expand_code;
	if (mode == GET)
		return (code);
	return (code);
}

void	ft_exit_if_malloc(t_data *data)
{
	if (ft_exit_code(0, GET) == 300)
	{
		ft_dup2_and_close_stdin_stdout(data, data->cmd_list);
		if (data->cmd_list->cmd_path)
			ft_free_tab(data->cmd_list->cmd_path);
		if (data->mini_env)
			ft_free_tab(data->mini_env);
		ft_clean_all(data);
		exit(ft_exit_code(255, ADD));
	}
}

void	ft_exit_if_malloc_parsing(t_data *data)
{
	if (ft_exit_code(0, GET) == 300)
	{
		if (data->mini_env)
			ft_free_tab(data->mini_env);
		ft_clean_all(data);
		exit(ft_exit_code(255, ADD));
	}
}
