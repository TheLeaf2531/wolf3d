/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:23:49 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/13 17:50:51 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		directional_keys(int key, t_env *e)
{
	t_vector2i	axis;
	t_vector2f	player_pos;


	//printf("key = %d \n", key);
	
	axis = (t_vector2i){(int)0, (int)0};
	player_pos = e->player->pos;
	if (key == 126) // upward
		axis.y = 1;
	if (key == 125) // downward
		axis.y = -1;
	if (key == 124) // right
		axis.x = -1;
	if (key == 123) // left
		axis.x = 1;
	if (axis.x != 0 || axis.y != 0)
	{
		move_player(e, axis);
		return (1);
	}
	return (0);
}

static int 		rotation_key(int key, t_env *e)
{
	int		r;

	r = 0;
	if (key == 83)
		r = -1;
	if (key == 84)
		r = 1;
	if (r != 0)
	{
		rotate_player(e, r);
		return (1);
	}
	return (0);
}

int				player_keyhook(int key, void *param)
{
	t_env	*e;
	int 	r;

	e = param;
	r = 0;
	r = rotation_key(key, e);
	r = !r ? directional_keys(key, e) : r;
	if (r != 0)
		render_level(e, e->map, e->player, (t_vector2i){WIDTH, HEIGHT});
	return (0);
}