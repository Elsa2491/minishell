/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:45:50 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/17 20:41:55 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_add_shlvl(t_data *data, char *value)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "SHLVL") == 0)
		{
			ft_free_ptr(tmp->value);
			tmp->value = ft_strdup(value);
			ft_free_ptr(value);
			if (!tmp->value)
				return (ft_exit_code(300, ADD), false);
		}
		tmp = tmp->next;
	}
	return (true);
}

static bool	ft_increase_shlvl(t_data *data)
{
	char	*shlvl;
	int		count;
	char	*count_str;

	if (ft_var_is_in_env(data, "SHLVL"))
	{
		shlvl = ft_var_is_exp(data, "SHLVL");
		if (!shlvl)
			return (ft_exit_code(300, ADD), false);
		count = ft_atoi(shlvl);
		count++;
		count_str = ft_itoa(count);
		if (!count_str)
			return (free(shlvl), ft_exit_code(300, ADD), false);
		ft_free_ptr(shlvl);
		if (!ft_add_shlvl(data, count_str))
			return (ft_exit_code(300, ADD), false);
	}
	return (true);
}

static t_env	*ft_no_env(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!ft_lstinit_env(&data->env, ft_strdup_exec(data, "SHLVL"),
			ft_strdup_exec(data, "2")))
		return (ft_exit_code(300, ADD), NULL);
	if (!ft_lstinit_env(&data->env, ft_strdup_exec(data, "PWD"),
			ft_strdup_exec(data, pwd)))
		return (ft_exit_code(300, ADD), NULL);
	if (!ft_lstinit_env(&data->env, ft_strdup_exec(data, "_"),
			ft_strdup_exec(data, "/usr/bin/env")))
		return (ft_exit_code(300, ADD), NULL);
	return (data->env);
}

void	ft_is_it_atty(t_data *data)
{
	int	fd;

	if (isatty(STDIN_FILENO) == 0)
	{
		ft_putstr_fd("Non-interactive mode blocked\n", 2);
		ft_clean_all(data);
		exit(ft_exit_code(0, GET));
	}
	if (isatty(0) == 1)
	{
		fd = open("/dev/stdin", O_RDWR);
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
}

void	ft_init_minish(t_data *data, char **env, int argc)
{
	int	i;

	i = 0;
	if (argc != 1)
		ft_print_wrong_param();
	ft_memset(data, 0, sizeof(t_data));
	while (i < 1024)
	{
		data->pidlist[i] = -1;
		i += 1;
	}
	if (env && env[0])
	{
		data->env = ft_get_env(data, env);
		if (ft_exit_code(0, GET) == 300)
			(ft_clean_all(data), exit(255));
		if (!ft_increase_shlvl(data))
			(ft_clean_all(data), exit(255));
	}
	else
		data->env = ft_no_env(data);
	if (ft_exit_code(0, GET) == 300)
		(ft_clean_all(data), exit(255));
}
