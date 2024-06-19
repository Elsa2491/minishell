/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/14 15:23:19 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_exec(t_data *data, char *s1, char *s2)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		(ft_exit_code(300, ADD), ft_exit_if_malloc(data));
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i += 1;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_exec(t_data *data, char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		(ft_exit_code(300, ADD), ft_exit_if_malloc(data));
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i += 1;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_exec(t_data *data, char *s, size_t start, size_t len)
{
	char			*subs;
	size_t			i;
	size_t			s_size;

	i = 0;
	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (start >= s_size)
		len = 0;
	if (len > s_size - start)
		len = s_size - start;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		(ft_exit_code(300, ADD), ft_exit_if_malloc(data));
	while (i < len)
	{
		subs[i] = s[start];
		start++;
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
