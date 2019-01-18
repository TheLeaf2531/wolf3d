/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:15:46 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/18 17:37:48 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_game_env	*init_game_env()
{
	t_game_env	*game_env;

	if (!(game_env = ft_memalloc(sizeof(game_env))))
		return (NULL);
	game_env->player = init_player();
	game_env->sector_count  = 1;
	if (!(game_env->sectors 
			= ft_memalloc(sizeof(t_sector*) * game_env->sector_count)))
		return (NULL);
	game_env->sectors[0] = get_sector(0);
	game_env->mapviewcam.is_set = 0;
	return (game_env);
}