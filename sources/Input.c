/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:23:49 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/10 18:38:12 by vboissel         ###   ########.fr       */
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
		axis.x = 1;
	if (key == 123) // left
		axis.x = -1;
	if (axis.x != 0 || axis.y != 0)
	{
		move_player(e, axis);
		render_level(e, e->level, e->player, (t_vector2i){WIDTH, HEIGHT});
	}
	return (0);
}

int				player_keyhook(int key, void *param)
{
	t_env	*env;

	env = param;
	directional_keys(key, env);

	return (0);
}