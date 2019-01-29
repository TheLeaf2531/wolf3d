/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:33:38 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/29 18:43:37 by vboissel         ###   ########.fr       */
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
	float 		pi;
	
/*
	if (p->rot <= 90 || p->rot >= 270)
		a.x = 1;
	else
		a.x = -1;
	a.y = 1 * tan(p->rot);
	//Py + (Px-A.x)*tan(ALPHA);
	inter.x = floor(p->pos.x) + 1;
	inter.y = p->pos.y - (p->pos.x - a.x) / tan(p->rot);
	printf("Intersection 1 {%f,%f}\n", inter.x, inter.y);
	inter.x += a.x;
	inter.y += a.y;
	printf("Intersection 1 {%f,%f}\n", inter.x, inter.y);
	*/
	
	//	HORIZONTAL SALE MERDE

	printf("Player rotation : %f\n", p->rot);
	if (p->rot >= 0 && p->rot <= 180)
		a.y = -1;
	else
		a.y = 1;
	if (p->rot >= 0 && p->rot <= 180)
		inter.y = roundf(p->pos.y) - 1;
	else
		inter.y = roundf(p->pos.y) + 1;
	p->rot = degreesToRadians(p->rot);
	a.x = 1.0 / tanf(p->rot);
	printf("Player position {%f,%f}\n", p->pos.x, p->pos.y);
	//printf("xa = %f, Ya = %f\n", a.x, a.y);
	//printf("%f\n", (1 - (ceilf(p->pos.y) - p->pos.y)));
	inter.x = p->pos.x + ((p->pos.y - inter.y) / tan(p->rot));
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