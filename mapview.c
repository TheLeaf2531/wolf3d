/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 19:23:46 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/18 20:07:08 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*
static int		is_sector_visible(t_sector *sector, t_mapviewcam cam)
{
	int		i;
	int		p_count;

	i = 0;
	p_count = sector->p_count;
	while (i < p_count)
	{
		if (sector->point[i].x > cam.viewport[0].x && 
			sector->point[i].x > cam.viewport[0].x)
	}
}
*/
static void		draw_sector(t_mlximg *img, t_sector *sector, t_mapviewcam cam)
{
	int				i;
	t_vector2f		points[2];
	t_vector2i		points_p[2];
	printf("\n");
	i = 0;
	while (i < sector->p_count )
	{
		points[0] = sector->point[i];
		points[1] = i == sector->p_count - 1 ? sector->point[0] : sector->point[i + 1];
		points_p[0] = (t_vector2i){
			(int)(-cam.viewport[0].x + points[0].x ) * cam.pixels_by_unit,
			(int)(-cam.viewport[0].y + points[0].y ) * cam.pixels_by_unit};
		points_p[1] = (t_vector2i){
			(int)(-cam.viewport[0].x + points[1].x ) * cam.pixels_by_unit,
			(int)(-cam.viewport[0].y + points[1].y ) * cam.pixels_by_unit};
		printf("Point %d {%f : %f}\n", i, points[0].x, points[0].y);
		printf("Point %d {%f : %f}\n\n", i + 1, points[1].x, points[1].y);
		printf("Point %d {%d : %d}\n", i, points_p[0].x, points_p[0].y);
		printf("Point %d {%d : %d}\n\n", i + 1, points_p[1].x, points_p[1].y);
		line(points_p[0], points_p[1], img, 0xD3D3D3);
		i++;
	}
}

static t_mapviewcam		set_camera(t_env *env, t_vector2i size)
{
	t_mapviewcam	camera;
	
	camera.position = env->game_env->player.pos;
	camera.pixels_by_unit = 64;
	camera.zoom_level = 1;
	camera.size = (t_vector2f){(float)size.x, (float)size.y};
	camera.viewport[0] = (t_vector2f){
		(float)(camera.position.x - (camera.size.x / 2 / camera.pixels_by_unit)),//ICI C'EST FAUX 
		(float)(camera.position.y - (camera.size.y / 2 / camera.pixels_by_unit))};//
	camera.viewport[1] = (t_vector2f){
		(float)(camera.position.x + (camera.size.x / 2 / camera.pixels_by_unit)),//
		(float)(camera.position.y + (camera.size.y / 2 / camera.pixels_by_unit))};//
	camera.is_set = 1;
	printf("Viewport srt {%f : %f}\n", camera.viewport[0].x, camera.viewport[0].y);
	printf("Viewport end {%f : %f}\n\n", camera.viewport[1].x, camera.viewport[1].y);
	return (camera);
}

static t_mlximg			*display_player(t_env *env, t_mlximg *img)
{
		float			direction_vector_lenght;
		int				i;
		t_mapviewcam	cam;

		direction_vector_lenght = 10;
		cam = env->game_env->mapviewcam;
		i = 0;
		printf("Player position : {%f, %f}\n", env->game_env->player.pos.x, env->game_env->player.pos.y);
		set_pixel((t_vector2i){(int)cam.size.x / 2, (int)cam.size.y/2},
					0x00aaff, img);
		return (img);
}

t_mlximg				*render_map_view(t_env *env, t_vector2i size)
{
	t_mapviewcam	camera;
	t_mlximg		*mapimg;
	int				i;

	if (!env->game_env->mapviewcam.is_set)
	{
		camera = set_camera(env, size);
		env->game_env->mapviewcam = camera;
	}
	else
		camera = env->game_env->mapviewcam;
	mapimg = new_mlximg(env->mlx_ptr, size.x, size.y);
	i = 0;
	printf("sector count : %d\n", env->game_env->sector_count);
	while (i < env->game_env->sector_count)
	{
		draw_sector(mapimg, env->game_env->sectors[i], camera);
		i++;
	}
	mapimg = display_player(env, mapimg);
	printf("ok\n");
	return (mapimg);
}











