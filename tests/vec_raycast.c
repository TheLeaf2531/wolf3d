/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:31:51 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/20 19:07:45 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

typedef struct	s_vector2
{
	float x;
	float y;
}				t_vector2;


int		main(void)
{
	t_vector2		wall[2];
	t_vector2		pos;
	t_vector2		rot;
	t_vector2		res;
	float			dis;
	float			mat[3][2];

	pos		= (t_vector2){(float) 7.0, (float)3.0};
	rot		= (t_vector2){(float)-1.0, (float)0.2};
	wall[0] = (t_vector2){(float) 4.0, (float)0.0};
	wall[1] = (t_vector2){(float) 0.0, (float)9.0};

	mat[0][0] =  rot.y;
	mat[1][0] = -rot.x;
	mat[2][0] = -(rot.x * pos.y - rot.y * pos.x);
	if (wall[0].x != wall[1].x)
	{
		mat[0][1] = (wall[1].y - wall[0].y) / (wall[1].x - wall[0].x);
		mat[1][1] = -1;
		mat[2][1] = -(wall[1].y - mat[0][1] * wall[1].x);
	}
	else
	{
		mat[0][1] = 1;
		mat[1][1] = 0;
		mat[2][1] = -wall[0].x;		
	}
	res.x = (mat[2][0] * mat[1][1] - mat[2][1] * mat[1][0]) /
			(mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
	res.y = (mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1] ) /
			(mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1]);
	dis = sqrtf((pos.x - res.x) + (pos.y - res.y)); 
	printf("( %f %f %f)\n", mat[0][0], mat[1][0], mat[2][0]);
	printf("( %f %f %f)\n", mat[0][1], mat[1][1], mat[2][1]);
	printf("res {%f ; %f}\n", res.x, res.y);
	printf("dis %f\n", dis);

	return (0);
}