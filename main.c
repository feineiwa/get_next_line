/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:50:14 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/15 14:29:03 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main()
{
	int	fd;
	char *line;

	fd = open("tests/text.txt", O_RDONLY);

	for (int  i = 0; i < 3; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	// while (1)
	// {
	// 	line = get_next_line(fd);
	// 	if (line == NULL)
	// 		break;
	// 	printf("%s", line);
	// 	free(line);
	// }
	// return (0);
}
