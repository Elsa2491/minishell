/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:15:47 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/16 21:53:56 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_args(t_token *token_list)
{
	t_token	*tmp;
	int		i;

	tmp = token_list;
	i = 0;
	while (tmp && tmp->type == WORD)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static char	**ft_new_args_tab(t_token **token_lst, t_cmds *last_cmd,
		char **new_args, int len)
{
	int	i;

	i = 0;
	while (last_cmd->args[i])
	{
		new_args[i] = ft_strdup(last_cmd->args[i]);
		if (!new_args[i])
			return (ft_exit_code(300, ADD), ft_free_tab(new_args), NULL);
		i++;
	}
	while (i < len)
	{
		new_args[i] = ft_strdup((*token_lst)->value);
		if (!new_args[i])
			return (ft_exit_code(300, ADD), ft_free_tab(new_args), NULL);
		i++;
		*token_lst = (*token_lst)->next;
	}
	new_args[i] = NULL;
	return (new_args);
}

bool	ft_set_more_args(t_cmds *last_cmd, t_token **token_lst)
{
	int		i;
	int		len;
	char	**added_args;
	t_token	*tmp;

	tmp = *token_lst;
	i = 0;
	while (last_cmd->args[i])
		i++;
	len = i + ft_count_args(tmp);
	added_args = malloc(sizeof(char *) * (len + 1));
	if (!added_args)
		return (false);
	added_args = ft_new_args_tab(&tmp, last_cmd, added_args, len);
	if (!added_args)
		return (false);
	ft_free_tab(last_cmd->args);
	last_cmd->args = added_args;
	*token_lst = tmp;
	return (true);
}

static bool	ft_add_args(t_token **token_list, t_cmds *last_cmd, int *index)
{
	while (*token_list && ((*token_list)->type == WORD))
	{
		last_cmd->args[*index] = ft_strdup((*token_list)->value);
		if (!last_cmd->args[*index])
			return (ft_exit_code(300, ADD), false);
		*token_list = (*token_list)->next;
		(*index)++;
	}
	return (true);
}

bool	ft_set_args(t_cmds *last_cmd, t_token **token_list)
{
	t_token	*tmp;
	int		nb;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = *token_list;
	nb = ft_count_args(tmp);
	last_cmd->args = malloc(sizeof(char *) * (nb + 2));
	if (!last_cmd->args)
		return (ft_exit_code(300, ADD), false);
	while (j++ <= nb)
		last_cmd->args[j] = NULL;
	last_cmd->args[i] = ft_strdup(last_cmd->cmd);
	if (!last_cmd->args[i])
		return (ft_exit_code(300, ADD), false);
	i++;
	if (!ft_add_args(&tmp, last_cmd, &i))
		return (false);
	last_cmd->args[i] = NULL;
	*token_list = tmp;
	return (true);
}
