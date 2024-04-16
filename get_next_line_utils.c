/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:30:51 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/16 12:37:10 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	push_in_stash(t_list **stash, char *buff)
{
	t_list	*new_list;
	t_list	*last_list;

	new_list = malloc(sizeof(t_list));
	last_list = ft_lstlast(*stash);
	if (new_list == NULL)
		return ;
	if (*stash == NULL)
		*stash = new_list;
	else
		last_list->next = new_list;
	new_list->content = buff;
	new_list->next = NULL;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}

int	found_new_line(t_list *stash)
{
	int	i;

	if (!stash)
		return (0);
	while (stash)
	{
		i = 0;
		while (stash->content[i] != '\0')
		{
			if (stash->content[i] == '\n')
				return (1);
			i++;
		}
		stash = stash->next;
	}
	return (0);
}
