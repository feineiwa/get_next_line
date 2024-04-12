/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:22:57 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/12 15:24:30 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void 	read_and_stashed(t_list **stash, int fd);
int		found_newline(t_list *stash);
void	push_in_stash(t_list **stash, char *buff);
t_list	*ft_lstlast(t_list *lst);
char	*extracted_line(t_list *stash);
int		len_line(t_list *stash);
void	ft_clean(t_list **stash);
void	ft_free(t_list **stash, char *buff, t_list *clean);


char	*gnl(int fd)
{
	static t_list	*stash = NULL;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//1.read from fd and to linked list
	
	read_and_stashed(&stash, fd);
	if (stash == NULL)
		return (NULL);
	
	//2.extract from stash to line
	line = extracted_line(stash);
	if (!line)
		return (NULL);
	//clean up the stash
	ft_clean(&stash);
	// printf("%s\n", stash->content);
	return (line);
}

void read_and_stashed(t_list **stash, int fd)
{
	int		rd;
	char	*buff;

	while (!found_newline(*stash))
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		rd = (int)read(fd, buff, BUFFER_SIZE);
		if (stash == NULL && rd == 0 || rd == -1)
		{
			free(buff);
			return ;
		}
		buff[rd] = '\0';
		push_in_stash(stash, buff);
	}
	while(!(*stash))
	{
		printf("%s", (*stash)->content);
		(*stash)->next;
	}
}

int	found_newline(t_list *stash)
{
	int	i;

	if (!stash)
		return (0);
	while (stash)
	{
		i = 0;
		while (stash->content[i])
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
	t_list	*new_node;
	t_list	*last_node;
	
	last_node = ft_lstlast(*stash);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (last_node == NULL)
		*stash = new_node;
	else
		last_node->next = new_node;
	new_node->content = buff;
	new_node->next = NULL;
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

char	*extracted_line(t_list *stash)
{
	char	*line;
	int		len;
	int		i;
	int		j;
	
	len = len_line(stash);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i] != '\0' && j < len)
		{
			line[j++] = stash->content[i++];
		}
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
		while (stash->content[i] != '\0')
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

void	ft_clean(t_list **stash)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	char	*buff;
	int		j;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	clean = malloc(sizeof(t_list));
	if (!stash || !buff)
	{
		free(buff);
		return ;
	}
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	j = 0;
	while (last->content[i] && last->content[++i])
		buff[j++] = last->content[i];
	buff[j] = '\0';
	clean->content = buff;
	clean->next = NULL;
	ft_free(stash, buff, clean);
}

int		ft_strlen(char *str)
{
	int	i;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_free(t_list **stash, char *buff, t_list *clean)
{
	t_list	*iter;
	
	if (*stash == NULL)
		return ;
	while (*stash)
	{
		iter = (*stash)->next;
		free((*stash)->content);
		free(*stash);
		*stash = iter;
	}
	*stash = NULL;
	if (clean->content[0])
		*stash = clean;
	else
	{
		free(buff);
		free(clean);
	}
}