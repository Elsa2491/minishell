/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmds_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:45:21 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/30 17:12:15 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_delone_redir(t_redir *redir_node, void (*del)(void *))
{
	if (redir_node->path)
		(*del)(redir_node->path);
	(*del)(redir_node);
}

void	ft_clear_redirlst(t_redir **redir_list, void (*del)(void *))
{
	t_redir	*temp;

	temp = NULL;
	while (*redir_list)
	{
		temp = (*redir_list)->next;
		ft_delone_redir(*redir_list, del);
		*redir_list = temp;
	}
}
