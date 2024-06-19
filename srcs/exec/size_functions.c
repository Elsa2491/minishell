/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:15:31 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/05 13:40:35 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_return_tab_size(t_data *data, int size)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		ft_exit_if_malloc(data);
	return (tab);
}

int	ft_lstsize_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	if (!env)
		return (0);
	while (env != NULL)
	{
		env = env->next;
		i += 1;
	}
	env = tmp;
	return (i);
}

int	ft_count_words(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_is_space(str[i]) && str[i] != 58)
			j += 1;
		while ((!ft_is_space(str[i]) && str[i] != 58) && str[i] != '\0')
			i += 1;
		while ((ft_is_space(str[i]) || str[i] == 58) && str[i] != '\0')
			i += 1;
	}
	return (j);
}

int	ft_count_size_of_word_colon(char *str)
{
	int	i;

	i = 0;
	while ((!ft_is_space(str[i]) && str[i] != 58) && str[i] != '\0')
		i += 1;
	return (i);
}

int	ft_count_size_of_word(char *str)
{
	int	i;

	i = 0;
	while (!ft_is_space(str[i]) && str[i] != '\0')
		i += 1;
	return (i);
}
