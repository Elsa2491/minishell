/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:12:16 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/05 13:42:20 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_init_mini_env(t_data *data, t_env *env)
{
	int		size;

	size = ft_lstsize_env(env);
	data->mini_env = ft_return_tab_size(data, size);
	data->mini_env[size] = NULL;
}

static char	**ft_fill_mini_env(t_data *data, t_env *env, int *i, char *val)
{
	if (!ft_strcmp(env->var, "PATH"))
		data->mini_env[*i] = ft_fill_tab(data, val);
	else
		data->mini_env[*i] = ft_fill_tab_colon(data, val);
	if (!data->mini_env[*i])
		return (ft_free_tab(data->mini_env));
	return (data->mini_env);
}

static char	**ft_return_mini_env(t_data *data, t_env *env)
{
	int		i;
	char	*var;
	char	*val;
	t_env	*tmp;

	tmp = env;
	i = 0;
	ft_init_mini_env(data, env);
	while (tmp != NULL)
	{
		var = ft_strjoin_exec(data, tmp->var, "=");
		if (tmp->value)
			val = ft_strjoin_exec(data, var, tmp->value);
		else
			val = ft_strdup_exec(data, var);
		ft_fill_mini_env(data, tmp, &i, val);
		ft_free_ptr(var);
		ft_free_ptr(val);
		i += 1;
		tmp = tmp->next;
	}
	return (data->mini_env);
}	

static char	*ft_strncmp_exec(t_data *data, char *str, int n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	ft_return_mini_env(data, data->env);
	if (!data->mini_env)
		return (NULL);
	while (data->mini_env[i])
	{
		j = 0;
		k = 0;
		while (data->mini_env[i][j] == str[k] && k <= n)
		{
			j += 1;
			k += 1;
			if (k == n)
				return (&data->mini_env[i][j]);
		}
		i += 1;
	}
	return (NULL);
}

void	ft_get_path(t_data *data, t_cmds *cmds)
{
	cmds->env_path = ft_strncmp_exec(data, "PATH=", 5);
	if (cmds->env_path)
	{
		cmds->cmd_path = ft_split_exec(data, cmds->env_path);
		if (!cmds->cmd_path)
			return ;
	}
	else
		cmds->cmd_path = NULL;
}
