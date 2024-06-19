/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/07 17:23:03 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_here_doc(t_cmds *cmds)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	while (tmp != NULL)
	{
		if (tmp->type == 2)
			cmds->here_doc_count += 1;
		tmp = tmp->next;
	}
	return (cmds->here_doc_count);
}

void	ft_is_max_here_doc_nb_reached(t_data *data, t_cmds *cmds)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (tmp != NULL)
	{
		tmp->here_doc_count = ft_count_here_doc(tmp);
		if (tmp->here_doc_count > 16)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("maximun here-doc count exceeded\n", 2);
			ft_close_hd_in_fork(data->cmd_list, NULL);
			ft_free_tab(tmp->cmd_path);
			if (tmp->hd_read)
				ft_free_tab(data->mini_env);
			ft_clear_redirlst(&tmp->redir, &ft_free_ptr);
			free(tmp->redir);
			tmp->cmd_path = NULL;
			data->mini_env = NULL;
			ft_clean_all(data);
			ft_exit_code(1, ADD);
			exit (2);
		}
		tmp = tmp->next;
	}
}
