/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/15 20:51:41 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_normal_str(char *str, size_t *i)
{
	size_t	start;
	char	*normal_str;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	normal_str = ft_substr(str, start, *i - start);
	if (!normal_str)
		return (ft_exit_code(300, ADD), NULL);
	return (normal_str);
}

static char	*ft_normal_dq_str(char *str, size_t *i)
{
	size_t	start;
	char	*dq_str;

	start = (*i);
	while (str[*i] && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	dq_str = ft_substr(str, start, *i - start);
	if (!dq_str)
		return (ft_exit_code(300, ADD), NULL);
	return (dq_str);
}

static char	*ft_exp_dquotes(t_data *data, char *str, size_t *i)
{
	char	*dq_str;

	dq_str = ft_strdup("\"");
	if (!dq_str)
		return (ft_exit_code(300, ADD), NULL);
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			dq_str = ft_strjoin_exp(dq_str, ft_classic_exp(data, str, i,
						QUOTES));
		else
			dq_str = ft_strjoin_exp(dq_str, ft_normal_dq_str(str, i));
		if (!dq_str)
			return (ft_exit_code(300, ADD), NULL);
	}
	(*i)++;
	dq_str = ft_strjoin_exp(dq_str, ft_strdup("\""));
	if (!dq_str)
		return (ft_exit_code(300, ADD), NULL);
	return (dq_str);
}

static char	*ft_exp_squotes(char *str, size_t *i)
{
	size_t	start;
	char	*sq_str;

	start = (*i);
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	sq_str = ft_substr(str, start, (*i) - start);
	if (!sq_str)
		return (ft_exit_code(300, ADD), NULL);
	return (sq_str);
}

char	*ft_expand(t_data *data, char *str)
{
	char	*exp_str;
	char	*tmp;
	size_t	i;

	exp_str = ft_strdup("");
	if (!exp_str)
		return (ft_exit_code(300, ADD), NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			exp_str = ft_strjoin_exp(exp_str, ft_exp_squotes(str, &i));
		else if (str[i] == '"')
			exp_str = ft_strjoin_exp(exp_str, ft_exp_dquotes(data, str, &i));
		else if (str[i] == '$')
		{
			tmp = ft_classic_exp(data, str, &i, NO_QUOTES);
			exp_str = ft_expand_bis(tmp, exp_str);
		}
		else
			exp_str = ft_strjoin_exp(exp_str, ft_normal_str(str, &i));
		if (!exp_str)
			return (ft_exit_code(300, ADD), NULL);
	}
	return (exp_str);
}
