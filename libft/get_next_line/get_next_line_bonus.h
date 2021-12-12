/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:06:34 by whazami           #+#    #+#             */
/*   Updated: 2021/09/11 02:15:03 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl_list
{
	int					fd;
	char				buffer[BUFFER_SIZE + 1];
	int					buf_index;
	struct s_gnl_list	*next;
}	t_gnl_list;

int			get_next_line(int fd, char **line);
char		*ft_strdup_gnl(const char *s, size_t size);
size_t		ft_strlen_gnl(const char *s, char c);
t_gnl_list	*ft_lstadd_back_gnl(t_gnl_list **alst, int fd);
void		ft_lstdelone_gnl(t_gnl_list *begin, int fd);

#endif
