/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:24 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/07 17:38:23 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_lstlast_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
	{
		env = env->next;
	}
	return (env);
}

void	ft_lstadd_back_env(t_env **env_lst, t_env *new_env)
{
	t_env	*lastelem;

	if (!env_lst || !new_env)
		return ;
	lastelem = ft_lstlast_env(*env_lst);
	if (lastelem == NULL)
		*env_lst = new_env;
	else
	{
		lastelem->next = new_env;
		new_env->prev = lastelem;
	}
}

t_env	*ft_lstnew_env(char *var, char *value)
{
	t_env	*newel;

	newel = malloc(sizeof(t_env));
	if (!newel)
		return (NULL);
	newel->value = value;
	newel->var = var;
	newel->next = NULL;
	newel->prev = NULL;
	return (newel);
}
