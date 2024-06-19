/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:11:37 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/13 20:22:39 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_only_spacetab(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] != 9 && str[i] != 32)
			return (false);
		i++;
	}
	return (true);
}

char	*ft_del_edge_spaces(char *str)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[i] == 9 || str[i] == 32)
		i++;
	while (str[len] == 9 || str[len] == 32)
			len--;
	new_str = ft_substr(str, i, len - i + 1);
	if (!new_str)
		return (ft_exit_code(300, ADD), NULL);
	return (new_str);
}

bool	ft_is_whitespace(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		return (true);
	else
		return (false);
}

bool	ft_is_sep(char *str, int i)
{
	int	type;

	type = ft_define_token_type(str, i);
	if ((type > 0 && type < 6) || str[i] == 32 || str[i] == 9)
		return (true);
	else
		return (false);
}

int	ft_define_token_type(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	if (str[i] == '<')
		return (RED_IN);
	if (str[i] == '>')
		return (RED_OUT);
	if (str[i] == 32 || str[i] == 9)
		return (WHITESPACE);
	else
		return (WORD);
}
