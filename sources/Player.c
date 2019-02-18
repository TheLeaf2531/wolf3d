/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:18:29 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/13 17:52:29 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_player	*init_player(t_env *e)
{
	if (!(e->player = ft_memalloc(sizeof(t_player))))
		return (NULL);
	e->player->pos = (t_vector2f){(float)0, (float)0};
	e->player->dir = (t_vector2f){(float)0, (float)0};
	e->player->canvas_plane = (t_vector2f){(float)0, (float)0.66};
	e->player->rot = 0;
	return (e->player);
}



/*

	new_rotation = (t_vector2f){
		(float)e->player->dir.x * cos(speed) - e->player->dir.y * sin(speed),
		(float)e->player->dir.x * sin(speed) + e->player->dir.y * cos(speed)
	};
*/

void		move_player(t_env	*e, t_vector2i	axis)
{
	t_vector2f	mvmnt;
	t_vector2f	d;

	//printf("%d %d\n", axis.x, axis.y);
	//mvmnt.x = axis.x != 0 ? PLAYER_SPEED * e->player->dir.x * axis.x + e->player->pos.x : e->player->pos.x;
	//mvmnt.y = axis.y != 0 ? PLAYER_SPEED * e->player->dir.y * axis.y + e->player->pos.y : e->player->pos.y;
	if (axis.y != 0)
	{
		mvmnt.x = PLAYER_SPEED * axis.y * e->player->dir.x + e->player->pos.x;
		mvmnt.y = PLAYER_SPEED * axis.y * e->player->dir.y + e->player->pos.y;
	}
	if (axis.x != 0)
	{
		d.x = e->player->dir.x  * cos(degreesToRadians(axis.x * 90)) - e->player->dir.y * sin(degreesToRadians(axis.x * 90));
		d.y = e->player->dir.x  * sin(degreesToRadians(axis.x * 90)) + e->player->dir.y * cos(degreesToRadians(axis.x * 90));
		mvmnt.x = PLAYER_SPEED * d.x + e->player->pos.x;
		mvmnt.y = PLAYER_SPEED * d.y + e->player->pos.y;
	}
	//printf ("player pos      : %f %f\n", e->player->pos.x, e->player->pos.y);
	//printf ("mvmnt           : %f %f\n", mvmnt.x, mvmnt.y);
	
	//printf ("size           : %f %f\n", e->map->size.x, e->map->size.y);
	if (mvmnt.x > 0 && mvmnt.y > 0 
		&& mvmnt.x < (float)e->map->size.x && mvmnt.y < (float)e->map->size.y)
	{
		if ((int)e->player->pos.x > (int)mvmnt.x)
			if (e->map->c[(int)mvmnt.x][(int)mvmnt.y].w_id[0] != 0)
				mvmnt.x = e->player->pos.x;
		if ((int)e->player->pos.x < (int)mvmnt.x)
			if (e->map->c[(int)mvmnt.x][(int)mvmnt.y].w_id[2] != 0)
				mvmnt.x = e->player->pos.x;
		if ((int)e->player->pos.y > (int)mvmnt.y)
			if (e->map->c[(int)mvmnt.x][(int)mvmnt.y].w_id[1] != 0)
				mvmnt.y = e->player->pos.y;
		if ((int)e->player->pos.y < (int)mvmnt.y)
			if (e->map->c[(int)mvmnt.x][(int)mvmnt.y].w_id[3] != 0)
				mvmnt.y = e->player->pos.y;
		//printf ("player new pos : %f %f\n", mvmnt.x, mvmnt.y);
		e->player->pos = mvmnt;
	}

	//if (e->level->tab[(int)floorf(e->player->pos.x + mvmnt.x)]
	//				 [(int)floorf(e->player->pos.y + mvmnt.y)][0] == '0')
	//{}
}

void		rotate_player(t_env	*e, int a)
{
	t_vector2f	new_rotation;
	float		speed;

	speed = degreesToRadians(PLAYER_ROTATION_SPEED * a);
	new_rotation = (t_vector2f){
		(float)e->player->dir.x * cos(speed) - e->player->dir.y * sin(speed),
		(float)e->player->dir.x * sin(speed) + e->player->dir.y * cos(speed)
	};
	e->player->dir = new_rotation;
	new_rotation = (t_vector2f){
		(float)e->player->canvas_plane.x * cos(speed) - e->player->canvas_plane.y * sin(speed),
		(float)e->player->canvas_plane.x * sin(speed) + e->player->canvas_plane.y * cos(speed)
	};
	e->player->canvas_plane = new_rotation;
}