/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:33:38 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/28 18:57:24 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		set_pixel(t_vector2i pos, unsigned int color, t_mlximg *img)
{
	if (pos.x < 0 || pos.x >= img->width || pos.y < 0 || pos.y >= img->height)
		return ;
	img->img[pos.y * img->width + pos.x] = color;
}

static t_player		*fov_calc(t_player *p, int size)
{
	p->fov_radius.x = fabs(p->fov + p->fov / 2); 
	p->fov_radius.y = fabs(p->fov - p->fov / 2);
	p->fov_ray_step = p->fov / (float)size;
	return (p);
}

void		render_level(t_level *level, t_player *p, t_vector2i size)
{
	t_vector2f	inter;
	t_vector2f	a;

	if (p->rot >= 0 && p->rot <= 180)
		a.y = -1;
	else
		a.y = 1;
	a.x = 1 / tan(p->rot);
	printf("Player position {%f,%f}\n", p->pos.x, p->pos.y);
	printf("xa = %f, Ya = %f\n", a.x, a.y);
	if (p->rot >= 0 && p->rot <= 180)
		inter.y = roundf(p->pos.y) - 1;
	else
		inter.y = roundf(p->pos.y) + 1;
	inter.x = p->pos.x + ((p->pos.y - inter.y) / sin(p->rot));
	//inter.x = p->pos.x + ((p->pos.y - inter.y) / tan(p->rot));
	printf("Intersection 1 {%f,%f}\n", inter.x, inter.y);

	inter.x += a.x;
	inter.y += a.y;
	printf("Intersection 2 {%f,%f}\n", inter.x, inter.y);

}


/*
 *  A vérifier si utile :  
 */
   
void		line(t_vector2i srt, t_vector2i end, t_mlximg *img, unsigned int color)
{
	t_vector2i d;
	t_vector2i s;
	int err;
	int err2;

	d = (t_vector2i){abs(end.x - srt.x), abs(end.y - srt.y)};
	s = (t_vector2i){(srt.x < end.x ? 1 : -1), (srt.y < end.y ? 1 : -1)};
	err = (d.x > d.y ? d.x : -d.y) / 2;
	while(1)
	{
		set_pixel(srt, color, img);
		if (srt.x == end.x && srt.y == end.y)
			break;
		err2 = err;
		if (err2 > -d.x)
		{
			err -= d.y;
			srt.x += s.x;
		}
		if (err2 < d.y)
		{
			err+= d.x;
			srt.y += s.y;
		}
	}
}