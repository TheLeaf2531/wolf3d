/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:18:34 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/27 18:12:11 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct	s_level
{
	int			width;
	int			height;
	char		***tab;
}				t_level;

typedef struct	s_vector2i
{
	int			x;
	int			y;
}				t_vector2i;

typedef struct	s_vector2f
{
	float		x;
	float		y;
}				t_vector2f;

typedef struct	s_mlximg
{
	void			*img_ptr;
	unsigned int	*img;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}				t_mlximg;

typedef struct	s_player
{
	t_vector2f	pos;
	float		rot;
	float		fov;
	t_vector2f	fov_radius;
	float 		fov_ray_step;
}				t_player;


typedef struct	s_env
{
	void			*mlx_ptr;
	void			*win_ptr;
}				t_env;

#endif