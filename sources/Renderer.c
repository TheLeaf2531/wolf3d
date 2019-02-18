/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:33:38 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/13 18:34:54 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		set_pixel(t_vector2i pos, unsigned int color, t_mlximg *img)
{
	if (pos.x < 0 || pos.x >= img->width || pos.y < 0 || pos.y >= img->height)
		return ;
	img->img[pos.y * img->width + pos.x] = color;
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
//void		render_level(t_env *env, t_level *level, t_player *p, t_vector2i size)
void		render_level(t_env *env, t_map *level, t_player *p, t_vector2i size)
{
	t_mlximg		*img;
	int				i;
	int				l_h;
	t_vector2i		line;
	t_ray			ray;
	unsigned int	color;
	
	img = new_mlximg(env->mlx_ptr, size.x, size.y, 0x000000);
	i = 0;
	//printf("\nRENDER STUFF\n");
	while (i < size.x)
	{
		//printf("x : %d\n", i);
		ray = cast_ray(p, level, i, size.x);
	//	printf("raycasted\n");
		l_h = (int)(size.y / ray.dist);
	//	printf("line lenght okay\n");
	
		line.x = -l_h / 2 + size.y / 2;
		line.x = line.x < 0 ? 0 : line.x;
		line.y = l_h / 2 + size.y / 2;
		line.y = line.y >= size.y ? size.y - 1 : line.y; 
	//	printf("line coordinate ok\n");

		if (ray.wallHit == 0)
			color = 0xffffff;
		if (ray.wallHit == 1)
			color = 0xff0000;
		if (ray.wallHit == 2)
			color = 0x00ff00;
		if (ray.wallHit == 3)
			color = 0x0000ff;
	//	printf("color okay\n");

		draw_line((t_vector2i){i, line.x},
		 	 (t_vector2i){i, line.y},
		  	 img,
		 	 color);
	//	printf("line drawn\n");
		
		i++;
	}
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, img->img_ptr, 0, 0);
}
