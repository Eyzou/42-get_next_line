/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:34:17 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/16 18:41:42 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lst_last(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list && list->next)
		list = list->next;
	return (list);
}

void	free_list(t_list **list, t_list *new_node, char *buf)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	tmp = *list;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free((*list));
		*list = tmp;
	}
	*list = NULL;
	if (new_node->content[0])
		*list = new_node;
	else
	{
		free(new_node);
		free(buf);
	}
}

int	find_new_line(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	copy(t_list *list, char *dest)
{
	int	i;
	int	j;

	j = 0;
	if (NULL == list)
		return ;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				dest[j++] = '\n';
				break ;
			}
			dest[j++] = list->content[i++];
		}
		list = list->next;
	}
	dest[j] = '\0';
}

int	len_to_new_line(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}
