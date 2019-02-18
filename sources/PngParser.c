/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PngParser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:34:54 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/12 13:40:46 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		open_png(char	*filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	count = 0;
	while (fd > 0 &&  count < 10 && get_next_line(fd, &line))
	{
		printf("%s\n", line);
		free(line);
		count++;
	}
}