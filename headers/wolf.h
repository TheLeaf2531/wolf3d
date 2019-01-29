/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:22:45 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/29 18:18:31 by vboissel         ###   ########.fr       */
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
# define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
# define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)




void		render_level(t_level *level, t_player *p, t_vector2i size);

t_level				*parse_map(char *file_name);

t_mlximg			*new_mlximg(void *mlx_ptr, int width, int height,
								unsigned int color);
void				free_mlximg(t_mlximg *img, t_env *env);
#endif