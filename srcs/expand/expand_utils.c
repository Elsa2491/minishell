/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:27:39 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/14 14:01:48 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_quotes(char *str)
{
	int		i;
	int		quote_nb;
	char	c;

	quote_nb = 0;
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c)
				i++;
			if (str[i] == c)
				quote_nb += 2;
		}
		i++;
	}
	return (quote_nb);
}

bool	ft_is_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (true);
	}
	return (false);
}

void	ft_remove_quotes_bis(char *str, char *new_str, int *i, int *j)
{
	char	c;

	while (str[*i])
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			c = str[*i];
			(*i)++;
			while (str[*i] != c)
				new_str[(*j)++] = str[(*i)++];
			if (str[*i] == c)
				(*i)++;
		}
		else
			new_str[(*j)++] = str[(*i)++];
	}
}

char	*ft_remove_quotes(char *str, int code)
{
	int		i;
	int		j;
	int		quote_nb;
	char	*new_str;

	i = 0;
	j = 0;
	quote_nb = ft_count_quotes(str);
	new_str = malloc(sizeof(char) * (ft_strlen(str) - quote_nb) + 1);
	if (!new_str)
		return (ft_free_ptr(str), ft_exit_code(300, ADD), NULL);
	ft_remove_quotes_bis(str, new_str, &i, &j);
	new_str[j] = '\0';
	if (code == 1)
		ft_free_ptr(str);
	return (new_str);
}

char	*ft_var_is_exp(t_data *data, char *str)
{
	t_env	*tmp;
	char	*dup_value;

	dup_value = NULL;
	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->var) == 0 && tmp->value)
		{
			dup_value = ft_strdup(tmp->value);
			if (!dup_value)
				return (ft_exit_code(300, ADD), NULL);
			return (dup_value);
		}
		tmp = tmp->next;
	}
	dup_value = malloc(sizeof(char));
	if (!dup_value)
		return (ft_exit_code(300, ADD), NULL);
	dup_value[0] = '\0';
	return (dup_value);
}
