/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:22:45 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/11 18:01:33 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include <math.h>
#include <pthread.h>
#include <stdio.h>

#include "types.h"
#include "libft.h"
#include "mlx.h"

# define SQR_SIZE 64 
# define WIDTH 1024
# define HEIGHT 720
# define PLAYER_SPEED 0.1
# define PLAYER_ROTATION_SPEED 0.1
# define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
# define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)




void					render_level(t_env *env, t_level *level, t_player *p, t_vector2i size);

t_level					*parse_map(char *file_name);

t_env					*init_mlx(void);

t_mlximg				*new_mlximg(void *mlx_ptr, int width, int height,
									unsigned int color);
void					free_mlximg(t_mlximg *img, t_env *env);

t_ray					cast_ray(t_player	*p, t_level	*l, int x, int size);
//float					cast_ray(t_vector2f srt, float angle, t_level *level);

t_player				*init_player(t_env *e);
void					move_player(t_env	*e, t_vector2i	axis);

int						player_keyhook(int key, void *param);
#endif