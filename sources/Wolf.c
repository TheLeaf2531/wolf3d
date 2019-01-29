/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:16:28 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/29 19:02:09 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(int argc, char **argv)
{
	t_level		*level;
	t_player	*player;

	if (argc != 2)
		return (0);
	if (!(level = parse_map(argv[1])))
		return (0);
	player = ft_memalloc(sizeof(t_player));
	player->fov = 60;
	player->pos = (t_vector2f){(float)1.5, (float)2.5};
	player->rot = 100;
	render_level(level, player, (t_vector2i){WIDTH, HEIGHT});
	return (0); 
}