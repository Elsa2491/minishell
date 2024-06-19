/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:21:55 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/13 19:57:58 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lsttoken_size(t_token *token)
{
	int	count;

	count = 0;
	if (!token)
		return (0);
	while (token != NULL)
	{
		token = token->next;
		count++;
	}
	return (count);
}

t_token	*ft_lstlast_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
	{
		token = token->next;
	}
	return (token);
}

void	ft_lstadd_back_token(t_token **token_lst, t_token *new_token)
{
	t_token	*lastelem;

	if (!token_lst || !new_token)
		return ;
	lastelem = ft_lstlast_token(*token_lst);
	if (lastelem == NULL)
		*token_lst = new_token;
	else
	{
		lastelem->next = new_token;
		new_token->prev = lastelem;
	}
}

t_token	*ft_lstnew_token(char *value, t_token_tp type, int flag)
{
	t_token	*newel;

	newel = malloc(sizeof(t_token));
	if (!newel)
		return (NULL);
	newel->value = value;
	newel->type = type;
	newel->flag_exp = flag;
	newel->next = NULL;
	newel->prev = NULL;
	return (newel);
}
