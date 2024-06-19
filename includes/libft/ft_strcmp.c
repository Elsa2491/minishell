/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:19:09 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/05 13:51:44 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *argv, const char *str)
{
	int	i;

	i = 0;
	if (!argv || !str)
		return (1);
	while (str[i] != '\0' && argv[i] != '\0' && argv[i] == str[i])
		i += 1;
	return (argv[i] - str[i]);
}
