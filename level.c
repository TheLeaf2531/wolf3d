/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:05:21 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/16 17:28:21 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	print_sector(t_sector *sector)
{
	int	i;

	i = 0;
	printf("Sector points : %d\n", sector->p_count);
	while (i < sector->p_count)
	{
		printf("Point %d {%f : %f}\n", i, sector->point[i].x, sector->point[i].y);
		i++;
	}
}

static t_sector	*fill_test_sector(t_sector * sector)
{
	sector->p_count = 5;
	if (!(sector->point = ft_memalloc(sizeof(t_vector2f*) * 5)))
		return (NULL);
	sector->point[0] = (t_vector2f){(float)0.0, (float)0.0};
	sector->point[1] = (t_vector2f){(float)0.0, (float)2.0};
	sector->point[2] = (t_vector2f){(float)0.0, (float)4.0};
	sector->point[3] = (t_vector2f){(float)3.0, (float)5.0};
	sector->point[4] = (t_vector2f){(float)3.0, (float)0.0};
	return (sector);
}

t_sector	*get_sector(int sector_id)
{
    t_sector	*sector;

	(void)sector_id;
    if (!(sector = ft_memalloc(sizeof(t_sector))))
        return (NULL);
    fill_test_sector(sector);
	print_sector(sector);
    return (sector);
}