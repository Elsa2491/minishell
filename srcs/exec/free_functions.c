/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:04:22 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/13 18:26:14 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i += 1;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

void	ft_free(t_data *data, t_cmds *tmp, char *cmd, char *error)
{
	t_cmds	*cmds;

	cmds = tmp;
	ft_close_hd_in_fork(data->cmd_list, NULL);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	while (cmds && cmds != NULL)
	{
		ft_free_tab(cmds->cmd_path);
		ft_free_tab(data->mini_env);
		cmds->cmd_path = NULL;
		data->mini_env = NULL;
		cmds = cmds->next;
	}
	ft_clean_all(data);
}
