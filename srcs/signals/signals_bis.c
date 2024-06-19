/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:57:37 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/07 17:33:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp_sig(char *argv, const char *str)
{
	int	i;
	int	res;

	i = 0;
	if (!argv || !str)
		return (1);
	while (str[i] != '\0' && argv[i] != '\0' && argv[i] == str[i])
		i += 1;
	res = argv[i] - str[i];
	ft_free_ptr(argv);
	if (res == 0)
		return (0);
	else
		return (1);
}
