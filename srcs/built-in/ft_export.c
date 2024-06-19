/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:04:50 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/15 14:56:19 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_add_value_only_bis(t_env *tmp, char *var, char *value, int code)
{
	char	*tmp_value;

	tmp_value = NULL;
	ft_free_ptr(var);
	if (code == 2)
		tmp->value = ft_strdup(value);
	else if (code == 3)
	{
		if (!tmp->value)
			tmp->value = ft_strdup("\0");
		tmp_value = ft_strjoin_exp(tmp->value, value);
		if (!tmp_value)
			return (ft_exit_code(300, ADD), false);
		tmp->value = ft_strdup(tmp_value);
	}
	if (!tmp->value)
		return (ft_exit_code(300, ADD), false);
	if (code == 2)
		ft_free_ptr(value);
	else if (code == 3)
		ft_free_ptr(tmp_value);
	if (tmp->next)
		tmp = tmp->next;
	return (true);
}

bool	ft_add_value_only(t_data *data, char *var, char *value, int code)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->var) == 0 && code == 2)
		{
			ft_free_ptr(tmp->value);
			if (!ft_add_value_only_bis(tmp, var, value, 2))
				return (ft_exit_code(300, ADD), false);
			else
				return (true);
		}
		else if ((ft_strcmp(var, tmp->var) == 0 && code == 3))
		{
			if (!ft_add_value_only_bis(tmp, var, value, 3))
				return (ft_exit_code(300, ADD), false);
			else
				return (true);
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	ft_add_var_and_value(t_data *data, char *str, int code)
{
	char	*var;
	char	*value;
	int		i;

	value = NULL;
	var = NULL;
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	var = ft_substr(str, 0, i);
	if (!var)
		return (ft_exit_code(300, ADD), false);
	if (code == 2)
		value = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	else if (code == 3)
		value = ft_substr(str, i + 2, ft_strlen(str) - i);
	if (!value)
		return (ft_free_ptr(var), ft_exit_code(300, ADD), false);
	if (code == 2 && (!ft_add_var_and_value_bis(data, var, value, 2)))
		return (ft_exit_code(300, ADD), false);
	if (code == 3 && (!ft_add_var_and_value_bis(data, var, value, 3)))
		return (ft_exit_code(300, ADD), false);
	return (true);
}

bool	ft_add_var_env(t_data *data, char *str, int code)
{
	t_env	*newel;

	if (code == 1 && !ft_var_is_in_env(data, str))
	{
		newel = ft_lstnew_env(str, NULL);
		if (!newel)
			return (false);
		ft_lstadd_back_env(&data->env, newel);
	}
	else if (code == 2)
	{
		if (!ft_add_var_and_value(data, str, 2))
			return (false);
	}
	else if (code == 3)
	{
		if (!ft_add_var_and_value(data, str, 3))
			return (false);
	}
	return (true);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		code;
	char	*dup_arg;

	code = 0;
	i = 1;
	if (!args[i])
		return (ft_display_export(data));
	while (args[i])
	{
		dup_arg = ft_strdup(args[i]);
		if (!dup_arg)
			return (ft_exit_code(300, ADD));
		if (dup_arg[0] == '-')
			return (ft_error_export(dup_arg, 2), ft_exit_code(0, GET));
		code = ft_check_export_case(dup_arg);
		if (code == 0)
			break ;
		if (ft_export_bis(data, dup_arg, code) != 0)
			return (ft_exit_code(0, GET));
		i++;
	}
	if (ft_exit_code(0, GET) != 300 && code != 0 && code != 1)
		ft_exit_code(0, ADD);
	return (ft_exit_code(0, GET));
}
