/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:16:28 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/19 17:13:26 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(int argc, char **argv)
{
	t_env		*env;

	if (argc != 2)
		return (0);
	env = init_mlx();
	//if (!(env->level = parse_map(argv[1])))
	//	return (0);
	if (!(env->map = load_map(argv[1])))
		return (0);
	if (!(env->player = init_player(env)))
		return (0);
	env->player->pos = (t_vector2f) {(float)4.1, (float)4};
	env->player->dir = (t_vector2f) {(float)-1.0, (float)0.0};
	env->player->canvas_plane = (t_vector2f) {(float)0, (float)0.66};
	render_level(env, env->map, env->player, (t_vector2i){WIDTH, HEIGHT});
	mlx_hook(env->win_ptr, 2, (1L << 2), &player_keyhook, env);
	mlx_loop(env->mlx_ptr);
	//open_png("imgs/texture_atlas.png");
	return (0); 
}