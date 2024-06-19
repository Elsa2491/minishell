/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:04:37 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/13 20:20:21 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_add_var_and_value_bis(t_data *data, char *var, char *value,
		int code)
{
	t_env	*newel;

	newel = NULL;
	if (!ft_var_is_in_env(data, var))
	{
		newel = ft_lstnew_env(var, value);
		if (!newel)
			return (ft_exit_code(300, ADD), false);
		ft_lstadd_back_env(&data->env, newel);
	}
	else if (code == 2 && !ft_add_value_only(data, var, value, 2))
		return (ft_exit_code(300, ADD), false);
	else if (code == 3 && !ft_add_value_only(data, var, value, 3))
		return (ft_exit_code(300, ADD), false);
	return (true);
}

t_env	*ft_create_export_env(t_data *data)
{
	t_env	*tmp;
	char	*exp_var;
	char	*exp_value;

	data->env_export = NULL;
	tmp = data->env;
	while (tmp)
	{
		exp_var = ft_strdup(tmp->var);
		if (!exp_var)
			return (ft_exit_code(300, ADD), NULL);
		if (tmp->value)
		{
			exp_value = ft_strdup(tmp->value);
			if (!exp_value)
				return (ft_exit_code(300, ADD), NULL);
		}
		else
			exp_value = NULL;
		if (!ft_lstinit_env(&data->env_export, exp_var, exp_value))
			return (ft_exit_code(300, ADD), NULL);
		tmp = tmp->next;
	}
	return (data->env_export);
}

int	ft_export_bis(t_data *data, char *dup_arg, int code)
{
	if (!ft_isalpha(dup_arg[0]) && dup_arg[0] != '_' && code != 0)
		return (ft_error_export(dup_arg, 1), 1);
	else if ((code >= 1 && code <= 3) && !ft_add_var_env(data, dup_arg,
			code))
		return (ft_exit_code(300, ADD));
	if (code == 2 || code == 3)
		ft_free_ptr(dup_arg);
	return (0);
}
