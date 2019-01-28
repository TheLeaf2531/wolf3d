/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mlximg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:59:21 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/27 17:59:07 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			fill_mlximg(t_mlximg *img, unsigned int color)
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

t_mlximg			*new_mlximg(void *mlx_ptr, int width, int height,
							unsigned int color)
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
	fill_mlximg(img, color);
	return (img);
}

void				free_mlximg(t_mlximg *img, t_env *env)
{
	mlx_destroy_image(env->mlx_ptr, img->img_ptr);
	free(img);
}