/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:07:17 by ehamm             #+#    #+#             */
/*   Updated: 2024/03/07 12:31:34 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstlast(t_list *lst);
void				dealloc(t_list **list, t_list *clean_node, char *buf);
int					find_new_line(t_list *list);
void				copy(t_list *list, char *dest);
int					len_to_new_line(t_list *list);
void				add_new_node(t_list **list, char *tmp);
void				read_and_stock_line(t_list **list, int fd);
char				*get_next_line(int fd);
char				*extract_from_list_to_line(t_list *list);
void				polish_list(t_list **list);

#endif
