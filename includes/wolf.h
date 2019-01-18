/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 19:15:00 by vboissel          #+#    #+#             */
/*   Updated: 2018/12/15 19:19:55 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include "libft.h"

typedef struct  s_env
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_env;


typedef struct  s_mapfile
{
    char    *fileName;
    char    **lines;
    size_t  size;
}               t_mapFile;

typedef struct  s_map
{
    char    *mapName;
}               t_map;

#endif