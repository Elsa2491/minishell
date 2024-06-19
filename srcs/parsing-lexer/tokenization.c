/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/14 16:37:15 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_tokenization(t_data *data)
{
	int		i;
	int		token_tp;
	char	*str;

	token_tp = 0;
	i = 0;
	str = ft_del_edge_spaces(data->input);
	if (!str)
		return (false);
	while (str[i] != '\0')
	{
		token_tp = ft_define_token_type(str, i);
		i = ft_add_token(data, str, token_tp, i);
		if (i == -1)
			return (ft_free_ptr(str), false);
	}
	ft_free_ptr(str);
	return (true);
}
