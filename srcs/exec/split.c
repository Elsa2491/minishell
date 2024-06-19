/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:27 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/17 01:15:52 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*ft_fill_tab_colon(t_data *data, char *str)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	size = ft_count_size_of_word_colon(str);
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		(ft_exit_code(300, ADD), ft_exit_if_malloc(data));
	while (str[i] != '\0' && str[i] != 58 && !ft_is_space(str[i]))
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_fill_tab(t_data *data, char *str)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	size = ft_count_size_of_word(str);
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		(ft_exit_code(300, ADD), ft_exit_if_malloc(data));
	while (str[i] != '\0' && !ft_is_space(str[i]))
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

static char	**ft_return_tab(t_data *data, char *str)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(str) + 1));
	if (!tab)
		(ft_exit_code(300, ADD), ft_exit_if_malloc(data));
	return (tab);
}

char	**ft_split_exec(t_data *data, char *str)
{
	int		j;
	char	**tab;

	j = 0;
	if (!str)
		return (NULL);
	tab = ft_return_tab(data, str);
	tab[ft_count_words(str)] = NULL;
	while (*str != '\0')
	{
		if (!ft_is_space(*str) && *str != 58)
		{
			tab[j] = ft_fill_tab_colon(data, str);
			if (!tab[j++])
				return (ft_free_tab(tab));
			while (*str != '\0' && *str != 58 && !(ft_is_space(*str)))
				str += 1;
		}
		else
			str += 1;
	}
	return (tab);
}
