/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:42:15 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/17 09:29:25 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void		read_from_fd(t_list **stash, int fd);
static char		*get_line(t_list *stash);
static int		len_line(t_list *stash);
static void		ft_free(t_list **stash);

char	*get_next_line(int fd)
{
	static t_list	*stash[1024];
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_from_fd(&stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	line = get_line(stash[fd]);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	ft_free(&stash[fd]);
	return (line);
}

void	read_from_fd(t_list **stash, int fd)
{
	char	*buff;
	int		rd;

	buff = NULL;
	while (!found_new_line(*stash))
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		rd = (int)read(fd, buff, BUFFER_SIZE);
		if (rd == 0 || rd == -1)
		{
			free(buff);
			return ;
		}
		while (rd <= BUFFER_SIZE)
			buff[rd++] = '\0';
		push_in_stash(stash, buff);
	}
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
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i] && (j < len))
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
	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
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

	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
	{
		remain = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!remain)
			return ;
		j = 0;
		i++;
		while (last->content[i])
			remain[j++] = last->content[i++];
		remain[j] = '\0';
		ft_lstclear(stash);
		*stash = NULL;
		*stash = ft_lstnew(remain);
	}
	else
		ft_lstclear(stash);
}
