/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:30:52 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/18 00:30:48 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_exp_question_m(t_data *data)
{
	char	*str;

	(void)data;
	str = ft_itoa(ft_exit_code(0, GET));
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_exp_pid(t_data *data)
{
	char	*str;
	int		pid;

	(void)data;
	pid = getpid();
	str = ft_itoa(pid);
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_exp_first_check(t_data *data, char *str, size_t **i)
{
	if (str[**i] == '\0')
		return (ft_strdup("$"));
	if (str[**i] == 32 || str[**i] == 9)
		return (ft_strdup("$"));
	if (str[**i] == '?')
		return ((**i)++, ft_exp_question_m(data));
	else if (str[**i] == '$')
		return ((**i)++, ft_exp_pid(data));
	else if (str[**i] == '\'' || str[**i] == '"')
		return (ft_strdup("\0"));
	return (NULL);
}

char	*ft_classic_exp(t_data *data, char *str, size_t *i, int code)
{
	size_t	start;
	char	*env_var;
	char	*env_value;

	(*i)++;
	if (str[*i] == '\0' || str[*i] == '?' || str[*i] == '$'
		|| str[*i] == '\'' || str[*i] == '"' || str[*i] == 32 || str[*i] == 9)
		return (ft_exp_first_check(data, str, &i));
	start = *i;
	ft_classic_exp_bis(str, i, code);
	env_var = ft_substr(str, start, *i - start);
	if (!env_var)
		return (NULL);
	env_value = ft_var_is_exp(data, env_var);
	if (!env_value)
		return (ft_free_ptr(env_var), NULL);
	if (env_value[0] == '\0')
		ft_add_code_exp(data);
	else
		env_value = ft_remove_space(env_value);
	if (!env_value)
		return (ft_free_ptr(env_var), NULL);
	else
		return (ft_free_ptr(env_var), env_value);
}

char	*ft_strjoin_exp(char *s1, char *s2)
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
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i += 1;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (ft_free_ptr(s1), ft_free_ptr(s2), str);
}
