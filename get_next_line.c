/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 07:40:10 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/05 16:57:56 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*read_and_stash(int	fd, t_list *stash);
char	*push_in_content(char *content, char *buff);
int	found_newline(char *str);

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	t_list			*ptr;
	char			*line;
	int		lengh;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lengh = 0;
	stash = malloc(sizeof(t_list));
	stash->content = NULL;
	stash->next = NULL;
	// 1. read from fd and to linked list
	ptr = read_and_stash(fd, stash);
	// 2. extract from stash to line
	int i;
	int j;
	int	len;

	j = 0;
	len = 0;
	t_list *tmp2 = ptr;
	while (ptr)
	{
		i = 0;
		while (ptr->content[i])
		{
			if (ptr->content[i] == '\n')
			{
				j = 1;
				break ;
			}
			printf("%c", ptr->content[i]);
			len++;
			i++;
		}
		if (j)
			break;
		ptr = ptr->next;
	}
	line = malloc((len + 1) * sizeof(char));
	int t = 0;
	j = 0;
	while (tmp2)
	{
		i = 0;
		while (tmp2->content[i])
		{
			if (tmp2->content[i] == '\n')
			{
				j = 1;
				break ;
			}
			line[t] = tmp2->content[i];
			t++;
			i++;
		}
		if (j)
			break;
		tmp2 = tmp2->next;
	}
	line[t] = '\0';
 	printf("\n%s", line);
	// 3. clean up stash
}

t_list	*read_and_stash(int	fd, t_list *stash)
{
	char	*buff;
	char	*tmp;
	t_list	*initial;
	int		rd;

	initial = stash;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	tmp = stash->content;
	while (!found_newline(tmp))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		buff[rd] = '\0';
	    stash->content = push_in_content(stash->content, buff);
		tmp = stash->content;
		if (stash->next == NULL)
		{
			stash->next = malloc(sizeof(t_list));
			stash->next->content = NULL;
			stash->next->next = NULL;
		}
		stash = stash->next;
	}
	return (initial);
}

char	*push_in_content(char *content, char *buff)
{
	int	i;

	i = 0;
	content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (buff[i])
	{
		content[i] = buff[i];
		i++;
	}
	content[i] = '\0';
	return (content);
}

int	found_newline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
