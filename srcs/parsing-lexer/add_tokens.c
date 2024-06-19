/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:36:16 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/14 16:39:29 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_add_word_bis(char *str, int *i, int *len)
{
	int	start_quote;

	while (str[*i] && !ft_is_sep(str, *i))
	{
		if (str[*i] && (str[*i] == '\'' || str[*i] == '"'))
		{
			start_quote = *i;
			*i = ft_check_end_quotes(str, *i, str[*i]);
			if (*i == 0)
				return (ft_error_quotes(), -1);
			else
				*len += *i - start_quote;
		}
		else
		{
			(*i)++;
			(*len)++;
		}
	}
	return (0);
}

static int	ft_add_word_tri(t_data *data, t_token **token_lst,
char *exp_value, char *value)
{
	t_token	*new_token;

	if (!exp_value)
		return (ft_free_ptr(value), ft_exit_code(300, ADD), -1);
	ft_free_ptr(value);
	if (ft_expand_code(0, GET) == 1 && ft_check_space_expand(exp_value))
	{
		if (!ft_add_exp_token(token_lst, exp_value) && ft_exit_code(0,
				GET) == 300)
			return (ft_exit_code(255, ADD), -1);
	}
	else
	{
		if (data->flag_null_exp == 1)
			new_token = ft_lstnew_token(exp_value, WORD, 1);
		else
			new_token = ft_lstnew_token(exp_value, WORD, 0);
		if (!new_token)
			return (ft_exit_code(300, ADD), -1);
		data->flag_null_exp = 0;
		ft_lstadd_back_token(token_lst, new_token);
	}
	ft_expand_code(0, ADD);
	return (0);
}

static int	ft_add_word_norm(t_data *data, t_token *tmp,
char *exp_value, char *value)
{
	if (tmp && tmp->type == HEREDOC)
	{
		exp_value = ft_remove_quotes(value, 0);
		if (!exp_value)
			return (ft_free_ptr(value), -1);
	}
	else
	{
		exp_value = ft_expand(data, value);
		if (!exp_value)
			return (ft_free_ptr(value), ft_exit_code(300, ADD), -1);
		exp_value = ft_remove_quotes(exp_value, 1);
		if (!exp_value)
			return (ft_free_ptr(value), ft_exit_code(300, ADD), -1);
	}
	if (ft_add_word_tri(data, &data->token_list, exp_value, value) == -1)
		return (-1);
	return (0);
}

static int	ft_add_word(t_data *data, t_token **token_lst, char *str, int i)
{
	int		len;
	int		start;
	char	*value;
	char	*exp_value;
	t_token	*tmp;

	exp_value = NULL;
	start = i;
	len = 0;
	tmp = ft_lstlast_token(*token_lst);
	if (ft_add_word_bis(str, &i, &len) == -1)
		return (ft_exit_code(2, ADD), -1);
	value = ft_substr(str, start, len);
	if (!value)
		return (ft_exit_code(300, ADD), -1);
	if (ft_add_word_norm(data, tmp, exp_value, value) == -1)
		return (-1);
	return (i);
}

int	ft_add_token(t_data *data, char *str, int type, int i)
{
	if (type > 0 && type < 6)
		i = ft_add_sep(&data->token_list, type, str, i);
	else if (type == 6)
		i = ft_add_word(data, &data->token_list, str, i);
	else
		i++;
	return (i);
}
