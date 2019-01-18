/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:28:56 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/16 15:47:24 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_player	init_player()
{
	t_player player;

	player.rotation_speed = 0.04;
	player.pos = (t_vector2f){(float)2.0, (float)5.0};
	player.rot = (t_vector2f){(float)-1.0, (float)-1.0};
	return (player);
}

t_player	rotate_player(t_player player, int left)
{
	t_vector2f	new_rotation;
	float		speed;
	
	speed = !(left) ? -player.rotation_speed : player.rotation_speed;
	new_rotation = (t_vector2f){
		(float)player.rot.x * cos(speed) - player.rot.y * sin(speed),
		(float)player.rot.x * sin(speed) - player.rot.y * cos(speed)
	};
	player.rot = new_rotation;
	return (player);
}

/**
 * 
 *
 **/

