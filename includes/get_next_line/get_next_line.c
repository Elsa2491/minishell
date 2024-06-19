/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:32:17 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:14:18 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr_gnl(t_gnl *node)
{
	int	i;

	if (!node)
		return (0);
	while (node)
	{
		i = 0;
		while (node->content[i] != '\0' && i < BUFFER_SIZE)
		{
			if (node->content[i] == '\n')
				return (1);
			i += 1;
		}
		node = node->next;
	}
	return (0);
}

void	ft_lstadd_back_gnl(t_gnl **list, char *buff)
{
	t_gnl	*last_node;
	t_gnl	*new_node;

	last_node = ft_lstlast_gnl(*list);
	new_node = malloc(sizeof(t_gnl));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buff;
	new_node->next = NULL;
}

void	ft_lstcreate_gnl(t_gnl **list, int fd)
{
	int		read_bytes;
	char	*buff;

	while (!ft_strchr_gnl(*list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (!read_bytes)
		{
			free(buff);
			return ;
		}
		buff[read_bytes] = '\0';
		ft_lstadd_back_gnl(list, buff);
	}
}

char	*get_line_gnl(t_gnl *node)
{
	int		str_size;
	char	*line;

	if (!node)
		return (NULL);
	str_size = ft_lstsize_gnl(node);
	line = malloc(str_size + 1);
	if (!line)
		return (NULL);
	ft_strcpy_gnl(node, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	*list = NULL;
	char			*next_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	ft_lstcreate_gnl(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line_gnl(list);
	ft_lstclean_gnl(&list);
	return (next_line);
}

/*
int    main(void)
{
    char    *line;
    int        fd1;
    int     i;

    i = 0;
    fd1 = open("test.txt", O_RDONLY);
    while (i < 500)
    {
        line = get_next_line(fd1);
        printf("line : %s", line);
        free(line);
        i++;
    }
    close(fd1);
    return (0);
}*/
