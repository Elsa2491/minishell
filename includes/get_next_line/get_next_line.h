/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:25:35 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:14:29 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

char	*get_next_line(int fd);
int		ft_strchr_gnl(t_gnl *node);
void	ft_lstadd_back_gnl(t_gnl **list, char *buff);
t_gnl	*ft_lstlast_gnl(t_gnl *node);
void	ft_lstcreate_gnl(t_gnl **list, int fd);
char	*get_line_gnl(t_gnl *node);
int		ft_lstsize_gnl(t_gnl *node);
void	ft_strcpy_gnl(t_gnl *node, char *line);
void	ft_lstclean_gnl(t_gnl **list);
void	ft_dealloc_gnl(t_gnl **list, t_gnl *node, char *rest);
#endif
