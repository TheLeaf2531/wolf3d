/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:24:38 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/28 18:19:14 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static	int			get_l_height(char *file_name)
{
	int			fd;
	char		*line;
	int			i;

	if ((fd = open(file_name, O_RDONLY)) <= 0)
		return (0);
	i = 0;
	while (get_next_line(fd, &line))
	{
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

static	t_level		*read_file(t_level *level, char *file_name)
{
	int			fd;
	char		*line;
	int			i;

	if ((fd = open(file_name, O_RDONLY)) <= 0)
		return (NULL);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(level->tab[i] = ft_strsplit(line, ' ')))
			return (NULL);
		free(line);
		i++;
	}
	close(fd);
	return (level);
}

static int			get_l_width(t_level *level)
{
	int i;
	int j;

	i = 0;
	while (level->tab[0][i])
	{
		i++;
	}
	level->width = i;
	i = 0;
	j = 0;
	while (level->tab[j])
	{
		while (level->tab[0][i])
				i++;
		if (i != level->width)
			return (0);
		i = 0;
		j++;
	}
	return (level->width);
}

t_level		*parse_map(char *file_name)
{
	t_level		*level;

	//printf("Start parsing of : %s\n", file_name);
	if (!(level = ft_memalloc(sizeof(t_level))))
		return (NULL);
	//printf("Level malloc done.\n");
	if (!(level->height = get_l_height(file_name)))
		return (NULL);
	//printf("Map Height : %d.\n", level->height);
	if (!(level->tab = ft_memalloc(sizeof(char**) * level->height)))
		return (NULL);
	//printf("Level tab malloc done.\n");
	if (!(level = read_file(level, file_name)))
		return (NULL);
	//printf("File reading done\n");
	if (!(get_l_width(level)))
		return (NULL);
	//printf("Width calc done\n");
	return (level);
}