/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:18:34 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/11 18:06:41 by vboissel         ###   ########.fr       */
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

typedef struct	s_vector2d
{
	double		x;
	double		y;
}				t_vector2d;

typedef	struct	s_ray
{
	int			hit;
	int			side;
	char		type;
	double		dist;
	double		wallDist;
	t_vector2i	map_coord;
	t_vector2d	ray_dir;
	t_vector2d	sideDist;
}				t_ray;

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
	t_vector2f	dir;
	t_vector2f	canvas_plane;

	t_vector2f	fov_radius;
	float		rot;
	float		fov;
	float 		fov_ray_step;
}				t_player;


typedef struct	s_env
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		*player;
	t_level			*level;
}				t_env;

#endif