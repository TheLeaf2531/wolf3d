/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:18:29 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/11 18:22:21 by vboissel         ###   ########.fr       */
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

void		move_player(t_env	*e, t_vector2i	axis)
{
	t_vector2f	mvmnt;

	mvmnt = (t_vector2f){(float)axis.x * PLAYER_SPEED,
						 (float)axis.y * PLAYER_SPEED};
	if (e->level->tab[(int)floorf(e->player->pos.x + mvmnt.x)]
					 [(int)floorf(e->player->pos.y + mvmnt.y)][0] == '0')
	{
		e->player->pos.x += mvmnt.x;
		e->player->pos.y += mvmnt.y;
	}
}