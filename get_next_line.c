/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 07:40:10 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/13 12:48:38 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_from_fd(t_list **stash, int fd);
int	found_new_line(t_list *stash);
void	push_in_stash(t_list **stash, char *buff);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
char	*get_line(t_list *stash);
int		len_line(t_list *stash);
void	ft_free(t_list **stash);

char	*get_next_line(int	fd)
{
	static t_list	*stash = NULL;
	char	*line;
	
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_from_fd(&stash, fd);
	if (stash == NULL)
		return (NULL);
	line = get_line(stash);
	ft_free(&stash);
	return (line);
}

void	read_from_fd(t_list **stash, int fd)
{
	char	*buff;
	int		rd;

	rd = -1;
	buff = NULL;
	while (!found_new_line(*stash))
	{
		if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return ;
		rd = (int)read(fd, buff, BUFFER_SIZE);
		if (rd == -1 || (rd == 0))
		{
			free(buff);
			buff = NULL;
			return ;
		}
		buff[rd] = '\0';
		push_in_stash(stash, buff);
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

void	push_in_stash(t_list **stash, char *buff)
{
	t_list	*new_list;
	t_list	*last_list;

	new_list = malloc(sizeof(t_list));
	new_list->next = NULL;
	new_list->content = buff;
	last_list = ft_lstlast(*stash);
	if (last_list == NULL)
		*stash = new_list;
	else
		last_list->next = new_list;
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

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	(*del)(lst->content);
	free(lst);
}

char	*get_line(t_list *stash)
{
	char	*line;
	int		len;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	len = len_line(stash);
	if (!(line = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i] && j < len)
			line[j++] = stash->content[i++];
		stash = stash->next;
	}
	line[j] = '\0';
	return (line);
}

int	len_line(t_list *stash)
{
	int	i;
	int	len;

	if (!stash)
		return (0);
	while(stash)
	{
		i = 0;
		while(stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				return (len);
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	return (len);
}

void	ft_free(t_list **stash)
{
	char	*remain;
	int		i;
	int		j;
	t_list	*last;
	
	if (!(remain = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return ;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	j = 0;
	while (last->content[++i])
		remain[j++] = last->content[i];
	remain[j] = '\0';
	ft_lstclear(stash, free);
	*stash = NULL;
	if (remain[0])
	{
		*stash = malloc(sizeof(t_list));
		(*stash)->content = malloc(sizeof(char) * j);
		(*stash)->content = remain;
		(*stash)->next = NULL;
	}
	else
	{
		free(remain);
		remain = NULL;
	}
}