/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:41:48 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/18 18:23:53 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


void		set_pixel(t_vector2i pos, unsigned int color, t_mlximg *img)
{
	if (pos.x < 0 || pos.x >= img->width || pos.y < 0 || pos.y >= img->height)
		return ;
	img->img[pos.y * img->width + pos.x] = color;
}

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

void		fill_img(t_mlximg *img, unsigned int color)
{
	size_t	img_size;
	size_t	i;

	img_size = img->width * img->height;
	i = 0;
	while (i < img_size)
	{
		img->img[i] = color;
		i++;
	}
}

t_mlximg	*new_mlximg(void *mlx_ptr, int width, int height)
{
	t_mlximg	*img;

	if ((img = ft_memalloc(sizeof(t_mlximg))) == NULL)
		return (NULL);
	if (!(img->img_ptr = mlx_new_image(mlx_ptr, width, height)))
		return (NULL);
	if (!(img->img = (unsigned int *)mlx_get_data_addr(
			img->img_ptr,
			&img->bpp,
			&img->size_line,
			&img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	fill_img(img, 0x404040);
	return (img);
}