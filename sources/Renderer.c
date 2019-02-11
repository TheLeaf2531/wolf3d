/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:33:38 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/11 18:47:53 by vboissel         ###   ########.fr       */
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
	//p->fov_radius.x = fabs(p->fov + p->fov / 2);
	p->fov_radius.x = p->rot - p->fov / 2;
	
	//p->fov_radius.y = fabs(p->fov - p->fov / 2);
	p->fov_radius.y = p->rot + p->fov / 2;
	p->fov_ray_step = p->fov / (float)size;
	return (p);
}

static void		draw_line(t_vector2i srt, t_vector2i end, t_mlximg *img, unsigned int color)
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


void		render_level(t_env *env, t_level *level, t_player *p, t_vector2i size)
{
	t_mlximg	*img;
	int			i;
	//float		rot;
	int			l_h;
	t_vector2i	line;
	//float		dist;
	//float		proj;
	t_ray		ray;
	
	img = new_mlximg(env->mlx_ptr, size.x, size.y, 0x000000);
	//p = fov_calc(p, size.x);
	//proj = (size.x / 2) / tanf(degreesToRadians(p->fov / 2));
	//printf("Proj : %f\n", proj);
	i = 0;
	while (i < size.x)
	{
		ray = cast_ray(p, level, i, size.x);
		/*
		rot = p->fov_radius.x + i * p->fov_ray_step;
		if (rot > 360)
			rot = fmodf(rot, 360);
		if (rot < 0)
			rot = 360 - rot;
		dist = cast_ray(p->pos, rot, level);
		dist = floorf((1 / dist) * proj);
		*/
		l_h = (int)(size.y / ray.dist);
		line.x = -l_h / 2 + size.y / 2;
		line.x = line.x < 0 ? 0 : line.x;
		line.y = l_h / 2 + size.y / 2;
		line.y = line.y >= size.y ? size.y - 1 : line.y; 
		draw_line((t_vector2i){i, line.x},
		 	 (t_vector2i){i, line.y},
		  	 img,
		 	 ray.side ? 0xD3D3D3 : 0xD3D3D3 / 2);
		/*
			line((t_vector2i){i, (int)(size.y / 2 - dist / 2)},
		 	 (t_vector2i){i, (int)(size.y / 2 + dist / 2)},
		  	 img,
		 	 0xD3D3D3);
		printf("Line (%d;%d) to (%d;%d)\n",
						(int)i,
						(int)(size.y / 2 - dist / 2),
						(int)i, 
						(int)(size.y / 2 + dist / 2));
		*/
		//printf("dist : %f\n", dist);
		i++;
	}
	//printf("done\n");
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, img->img_ptr, 0, 0);
}


/*
 *  A vérifier si utile :  
 */
   
