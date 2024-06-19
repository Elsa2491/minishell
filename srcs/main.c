/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/17 20:46:38 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_sig_exit;

static bool	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	if (ft_is_only_spacetab(str))
		return (false);
	if (!ft_tokenization(data))
		return (false);
	if (ft_check_syntax(data) != 0)
		return (false);
	if (!ft_get_cmds(data, &data->token_list))
		return (false);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	g_sig_exit = 0;
	ft_init_minish(&data, env, argc);
	ft_is_it_atty(&data);
	while (1)
	{
		ft_handle_signal();
		data.input = readline("minishell$ ");
		if (!data.input)
			return (ft_clean_all(&data), ft_putstr_fd("exit\n", 1),
				ft_exit_code(0, GET));
		if (ft_parsing(data.input, &data))
			ft_exec(&data, data.cmd_list);
		ft_waitpid(&data);
		if (ft_exit_code(0, GET) == 300)
			break ;
		ft_free_data(&data);
	}
	ft_clean_all(&data);
	if (ft_exit_code(0, GET) == 300)
		ft_exit_code(255, ADD);
	return (ft_exit_code(0, GET));
}
