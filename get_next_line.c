/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:34:19 by ehamm             #+#    #+#             */
/*   Updated: 2024/03/07 12:31:35 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_new_node(t_list **list, char *tmp)
{
	t_list	*new_node;
	t_list	*last;

	last = ft_lstlast(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last)
		*list = new_node;
	else
		last->next = new_node;
	new_node->content = tmp;
	new_node->next = NULL;
}

void	read_and_stock_line(t_list **list, int fd)
{
	char	*tmp;
	int		char_count;

	while (!find_new_line(*list))
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (NULL == tmp)
			return ;
		char_count = read(fd, tmp, BUFFER_SIZE);
		if (char_count <= 0)
		{
			free(tmp);
			return ;
		}
		tmp[char_count] = '\0';
		add_new_node(list, tmp);
	}
}

char	*extract_from_list_to_line(t_list *list)
{
	int		len;
	char	*str;

	if (NULL == list)
		return (NULL);
	len = len_to_new_line(list);
	str = malloc(len + 1);
	if (NULL == str)
		return (NULL);
	copy(list, str);
	return (str);
}

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] && last_node->content[++i])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stock_line(&list, fd);
	if (list == NULL)
		return (NULL);
	line = extract_from_list_to_line(list);
	polish_list(&list);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	close(fd);
	return (0);
}*/