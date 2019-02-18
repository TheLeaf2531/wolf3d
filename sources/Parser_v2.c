/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:45:35 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/12 16:09:10 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_map	*get_map_info(t_map *m, int fd)
{
	char	*l;
	char	**tab;

	get_next_line(fd, &l);
	if (!(tab = ft_strsplit(l, ' ')))
		return (NULL);
	m->size.x = ft_atoi(tab[0]);
	m->size.y = ft_atoi(tab[1]);
	free (tab[0]);
	free (tab[1]);
	free (tab);
	free (l);
	if (m->size.x <= 0 || m->size.y <= 0)
	{
		free (m);
		return (NULL);
	}
	return (m);
}

static t_map			*init_cases(t_map *m)
{
	int x;
	int y;
	int i;

	i = -1;
	x = -1;
	y = -1;
	if (!(m->c = ft_memalloc(sizeof(t_case) * m->size.x)))
		return (NULL);
	while (++i < m->size.x)
	{
		if (!(m->c[i] = ft_memalloc(sizeof (t_case) * m->size.y)))
			return (NULL);
	}
	while (x++ < m->size.x)
		while (y++ < m->size.y)
		{
			m->c[x][y].w_id[0] = 0;
			m->c[x][y].w_id[1] = 0;
			m->c[x][y].w_id[2] = 0;
			m->c[x][y].w_id[3] = 0;
			m->c[x][y].f_id = 1;
		}
	return (m);
}

static t_map	*populate_cases(t_map *m, int fd)
{
	char		*l;
	char		**t;
	t_vector2i	c;

	while (get_next_line(fd, &l))
	{
		t = ft_strsplit(l, ' ');
		c = (t_vector2i){ft_atoi(t[0]), ft_atoi(t[1])};
		if (c.x < 0 || c.x >= m->size.x || c.y < 0 || c.y >= m->size.y)
			return (NULL);
		m->c[c.x][c.y].w_id[0] = ft_atoi(t[2]);
		m->c[c.x][c.y].w_id[1] = ft_atoi(t[3]);
		m->c[c.x][c.y].w_id[2] = ft_atoi(t[4]);
		m->c[c.x][c.y].w_id[3] = ft_atoi(t[5]);
		m->c[c.x][c.y].f_id = ft_atoi(t[6]);
		free (l);
		free (t);
	}
	return (m);
}

t_map			*load_map(char *filename)
{
	int		fd;
	t_map	*m;
	int 	i;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (NULL);
	if (!(m = ft_memalloc(sizeof(t_map))))
		return (NULL);
	if (!(m = get_map_info(m, fd)))
		return (NULL);
	if (!(init_cases(m)))
		return (NULL);
	if (!(populate_cases(m, fd)))
		return (NULL);
	//printf("case 0 3 walls E:%d S:%d W:%d N:%d", m->c[3][0].w_id[0], m->c[3][0].w_id[1], m->c[3][0].w_id[2], m->c[3][0].w_id[3]);
	return (m);
}