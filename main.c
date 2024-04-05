/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:50:14 by frahenin          #+#    #+#             */
/*   Updated: 2024/04/05 15:55:57 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main()
{
	int	fd;
	char *line;

	fd = open("tests/text.txt", O_RDONLY);

	get_next_line(fd);
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