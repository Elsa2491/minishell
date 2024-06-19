/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:10:40 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/13 20:34:04 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_end_quotes(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
	{
		i++;
		return (i);
	}
	else
		return (0);
}

int	ft_add_sep(t_token **token_lst, int type, char *str, int i)
{
	int		len;
	char	*value;
	t_token	*new_token;

	if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	value = ft_substr(str, i, len);
	if (!value)
		return (ft_exit_code(300, ADD), -1);
	i += len;
	new_token = ft_lstnew_token(value, type, 0);
	if (!new_token)
		return (ft_exit_code(300, ADD), -1);
	ft_lstadd_back_token(token_lst, new_token);
	return (i);
}

bool	ft_check_space_expand(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32 && str[i] != 58)
			j += 1;
		while (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32 && str[i] != 58
			&& str[i] != '\0')
			i += 1;
		while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 58)
			&& str[i] != '\0')
			i += 1;
	}
	if (j >= 2)
		return (true);
	else
		return (false);
}

static bool	ft_add_exp_token_bis(t_token **token_lst, char *str, char *cmd,
		int *i)
{
	t_token	*rest_token;
	int		start;
	char	*arg;

	arg = NULL;
	while (str[*i] && (str[*i] == 32 || str[*i] == 9))
		(*i)++;
	start = *i;
	while (str[*i])
		(*i)++;
	arg = ft_substr(str, start, *i - start);
	if (!arg)
		return (ft_exit_code(300, ADD), false);
	rest_token = ft_lstnew_token(arg, WORD, 0);
	if (!rest_token)
		return (ft_free_ptr(cmd), ft_free_ptr(arg), ft_exit_code(300, ADD),
			false);
	ft_lstadd_back_token(token_lst, rest_token);
	return (true);
}

bool	ft_add_exp_token(t_token **token_lst, char *str)
{
	int		i;
	int		start;
	char	*cmd;
	t_token	*new_token;

	cmd = NULL;
	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == 9))
		i++;
	start = i;
	while (str[i] && str[i] != 32 && str[i] != 9)
		i++;
	cmd = ft_substr(str, start, i - start);
	if (!cmd)
		return (ft_exit_code(300, ADD), false);
	new_token = ft_lstnew_token(cmd, WORD, 0);
	if (!new_token)
		return (ft_free_ptr(cmd), ft_exit_code(300, ADD), false);
	ft_lstadd_back_token(token_lst, new_token);
	if (!ft_add_exp_token_bis(token_lst, str, cmd, &i))
		return (false);
	return (ft_free_ptr(str), true);
}
