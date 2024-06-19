/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:34:32 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/13 20:21:10 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_cmd_word_bis(t_token *tmp, t_cmds *last_cmd)
{
	last_cmd->cmd = ft_strdup(tmp->value);
	if (!last_cmd->cmd)
		return (ft_exit_code(300, ADD), false);
	tmp = tmp->next;
	return (true);
}

static bool	ft_cmd_word(t_cmds **cmd_list, t_token **token_list)
{
	t_cmds	*last_cmd;
	t_token	*tmp;

	tmp = *token_list;
	while (tmp && tmp->type == WORD)
	{
		last_cmd = ft_last_cmd(*cmd_list);
		if (!tmp->prev || (tmp->prev && tmp->prev->type == PIPE)
			|| !last_cmd->cmd)
		{
			if ((tmp->flag_exp == 0) && (!ft_cmd_word_bis(tmp, last_cmd)))
				return (false);
			else
				tmp = tmp->next;
		}
		else if (last_cmd && !last_cmd->args && !ft_set_args(last_cmd, &tmp))
			return (false);
		else if (last_cmd && last_cmd->args && last_cmd->redir
			&& !ft_set_more_args(last_cmd, &tmp))
			return (false);
	}
	*token_list = tmp;
	return (true);
}

static bool	ft_no_arg_cmd(t_data *data)
{
	t_cmds	*temp;

	if (!data || !data->cmd_list)
		return (false);
	temp = data->cmd_list;
	while (temp)
	{
		if (temp->cmd && !temp->args)
		{
			temp->args = malloc(sizeof(char *) * 2);
			if (!temp->args)
				return (false);
			temp->args[0] = ft_strdup(temp->cmd);
			if (!temp->args[0])
				return (false);
			temp->args[1] = NULL;
		}
		temp = temp->next;
	}
	return (true);
}

static bool	ft_set_new_cmd(t_data *data, t_token **token_lst)
{
	t_cmds	*new_cmd;

	if (!(*token_lst)->prev || (*token_lst)->type == PIPE)
	{
		new_cmd = lst_new_cmd();
		ft_memset(new_cmd, 0, sizeof(t_cmds));
		if (!new_cmd)
			return (ft_exit_code(300, ADD), false);
		lst_add_back_cmd(&data->cmd_list, new_cmd);
		if ((*token_lst)->type == PIPE)
			*token_lst = (*token_lst)->next;
	}
	return (true);
}

bool	ft_get_cmds(t_data *data, t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (tmp)
	{
		if (!ft_set_new_cmd(data, &tmp))
			return (false);
		if ((!tmp->prev && tmp->type == WORD) || (tmp->prev && tmp->type == WORD
				&& (tmp->prev->type == PIPE || tmp->prev->type == WORD)))
		{
			if (!ft_cmd_word(&data->cmd_list, &tmp))
				return (false);
		}
		else if (tmp->type < PIPE)
		{
			if (!ft_redir_cmd(&data->cmd_list, &tmp, tmp->type))
				return (false);
		}
		else
			break ;
	}
	if (!ft_no_arg_cmd(data))
		return (false);
	return (true);
}
