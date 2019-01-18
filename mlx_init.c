/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:58:53 by vboissel          #+#    #+#             */
/*   Updated: 2019/01/16 14:59:01 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env			*init_mlx(void)
{
	t_env	*e;

	if (!(e = ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(e->mlx_ptr = mlx_init()))
		return (NULL);
	if (!(e->win_ptr = mlx_new_window(e->mlx_ptr, WIDTH, HEIGHT, "Fractol")))
		return (NULL);
	return (e);
}