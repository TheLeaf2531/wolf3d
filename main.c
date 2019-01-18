/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:56:16 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/18 18:26:28 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int     main(void)
{
    t_env		*env;
	t_mlximg	*img;
    env = init_mlx();
	env->game_env = init_game_env();

	img = render_map_view(env, (t_vector2i){WIDTH, HEIGHT});
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, img->img_ptr, 0, 0);
	mlx_loop(env->mlx_ptr);
    return (0);
}