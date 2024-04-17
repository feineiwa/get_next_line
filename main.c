/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:33 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/17 18:47:24 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
	int	fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	for (int i = 0; i<10 ; i++)
	{
		line = (get_next_line(fd));
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
