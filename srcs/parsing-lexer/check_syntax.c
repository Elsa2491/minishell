/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:43:49 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/17 15:48:29 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_syntax(t_data *data)
{
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		if (!token->prev && token->type == PIPE)
			return (ft_syntax_error(token->value), ft_exit_code(2, ADD));
		if (token->type == PIPE && token->prev && token->prev->type == PIPE)
			return (ft_syntax_error(token->value), ft_exit_code(2, ADD));
		if (token->type < PIPE)
		{
			if (token->next && token->next->type < WORD)
			{
				return (ft_syntax_error(token->next->value), ft_exit_code(2,
						ADD));
			}
		}
		if (token->type == PIPE && !token->next)
			return (ft_syntax_error(token->value), ft_exit_code(2, ADD));
		if (token->type < PIPE && !token->next)
			return (ft_syntax_error("newline"), ft_exit_code(2, ADD));
		token = token->next;
	}
	return (0);
}
