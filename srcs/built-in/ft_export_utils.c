/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:04:27 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/15 14:57:54 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_var_is_in_env(t_data *data, char *str)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->var) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	ft_check_export_case(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (3);
		else if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			ft_error_export(str, 1);
			return (0);
		}
		else if (str[i] == '=')
			return (2);
		i++;
	}
	return (1);
}

void	ft_error_export(char *str, int code)
{
	int	i;

	i = 0;
	if (code == 1)
	{
		ft_putstr_fd("minishell: export: '", 2);
		while (str[i])
		{
			write(2, &str[i], 1);
			i++;
		}
		ft_putstr_fd("': not a valid identifier\n", 2);
		ft_exit_code(1, ADD);
	}
	else if (code == 2)
	{
		ft_putstr_fd("minishell: export: -", 2);
		write(1, &str[1], 1);
		ft_putstr_fd(": invalid option\n", 2);
		ft_exit_code(2, ADD);
		ft_free_ptr(str);
	}
	ft_free_ptr(str);
}

void	ft_order_export_env(t_env **export_env)
{
	t_env	*node;
	char	*tmp;

	if (!*export_env)
		return ;
	node = *export_env;
	while (node->next)
	{
		if (ft_strcmp(node->var, node->next->var) > 0)
		{
			tmp = node->next->var;
			node->next->var = node->var;
			node->var = tmp;
			tmp = node->next->value;
			node->next->value = node->value;
			node->value = tmp;
			node = *export_env;
		}
		else
			node = node->next;
	}
}

int	ft_display_export(t_data *data)
{
	t_env	*sorted_env;

	data->env_export = ft_create_export_env(data);
	if (!data->env_export)
		return (ft_exit_code(0, GET));
	sorted_env = data->env_export;
	ft_order_export_env(&sorted_env);
	while (sorted_env)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(sorted_env->var, 1);
		if (sorted_env->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(sorted_env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		sorted_env = sorted_env->next;
	}
	if (data->env_export)
		ft_free_env(data->env_export);
	return (ft_exit_code(0, GET));
}
