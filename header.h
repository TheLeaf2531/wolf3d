/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:24:53 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/18 19:57:10 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <math.h>
#include <pthread.h>
#include "libft.h"
#include "mlx.h"

#include <stdio.h>
#include <math.h>

# define WIDTH 600
# define HEIGHT 800

typedef struct	s_vector2f
{
	float x;
	float y;
}				t_vector2f;

typedef struct	s_vector2i
{
	int x;
	int y;
}				t_vector2i;

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
	t_vector2f	rot;
	float		rotation_speed;
}				t_player;

typedef struct	s_sector
{
	int			p_count;
	t_vector2f	*point;
}				t_sector;


typedef struct	s_mapviewcam
{
	t_vector2f	position;
	int			zoom_level;
	float		pixels_by_unit;
	t_vector2f	size;
	t_vector2f	viewport[2];
	int			is_set;
}				t_mapviewcam;

typedef struct	s_game_env
{
	int				sector_count;
	t_mapviewcam	mapviewcam;
	t_player		player;
	t_sector		**sectors;
}				t_game_env;

typedef struct	s_env
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_game_env		*game_env;	
}				t_env;

t_env			*init_mlx(void);

t_sector		*get_sector(int sector_id);


t_player		init_player();
t_player		rotate_player(t_player player, int left);

t_game_env		*init_game_env();

void			set_pixel(t_vector2i pos, unsigned int color, t_mlximg *img);
void			line(t_vector2i srt, t_vector2i end, t_mlximg *img, unsigned int color);
void			fill_img(t_mlximg *img, unsigned int color);
t_mlximg		*new_mlximg(void *mlx_ptr, int width, int height);


t_mlximg		*render_map_view(t_env *env, t_vector2i size);
/*

typedef struct	s_vector2d
{
	double x;
	double y;
}				t_vector2d;

typedef	struct	s_vector2l
{
	int		x;
	int		y;
}				t_vector2l;

typedef struct	s_vector2i
{
	int x;
	int y;
}				t_vector2i;

typedef	struct	s_image
{
	void			*img_ptr;
	unsigned int	*img;
	int				bpp;
	int				size_line;
	int				endian;
}				t_image;

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_vector2d 	pos;
	t_vector2d 	dir;
	t_vector2d 	plane;
	int worldMap[24][24];
}				t_env;

typedef struct	s_player
{
	t_vector2d	position;
	t_vector2d	rotation;
	t_vector2d	camera_plane;
}				t_player;

typedef	struct	s_ray
{
	t_vector2i	step;
	t_vector2i	start;
	t_vector2d	dir;
	t_vector2d	fside_dist;
	t_vector2d	delta_dist;
}				t_ray;

typedef	struct	s_rayhit
{
	int			hit;
	int			side_hit;
	t_vector2d	lenght;
}				t_rayhit;

t_vector2i		set_vec2i(int x, int y);
t_vector2d		set_vec2d(double x, double y);

*/
#endif