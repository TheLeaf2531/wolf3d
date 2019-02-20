/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:23:28 by vboissel          #+#    #+#             */
/*   Updated: 2019/02/19 17:25:17 by vboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

//old :
//static	t_ray	raycast_dda(t_level *l, t_ray ray, t_vector2d itrsec_dist, t_vector2i step)

static	t_ray	raycast_dda(t_map *l, t_ray ray, t_vector2d itrsec_dist, t_vector2i step)
{
	ray.hit = 0;
	int s = 0;
	if (ray.ray_dir.y == 0 && ray.ray_dir.x == -1)
	{
		printf (" 			Start \n");
		printf ("step :				(%d ; %d)\n", step.x, step.y);
		printf ("ray.ray_dir :		(%f ; %f)\n", ray.ray_dir.x, ray.ray_dir.y);
		printf ("ray.map_coord.x :	(%d ; %d)\n", ray.map_coord.x, ray.map_coord.y);
		printf ("ray.itrsec_dist:	(%f ; %f)\n", itrsec_dist.x, itrsec_dist.y);	
		printf ("ray.sideDist :		(%f ; %f)\n", ray.sideDist.x, ray.sideDist.y);

	}	
	while (!ray.hit)
	{
		if (ray.ray_dir.y == 0 && ray.ray_dir.x == -1)
			printf("\nSTEP : %d\n", s);
		//printf("coord %d %d\n", ray.map_coord.x, ray.map_coord.y);
		if (ray.sideDist.x < ray.sideDist.y)
		{
			ray.sideDist.x += itrsec_dist.x;
			ray.map_coord.x += step.x;
			ray.side = 0;
			ray.wallHit = ray.ray_dir.x > 0 ? 0 : 2;
			if (ray.ray_dir.y == 0 && ray.ray_dir.x == -1)
			{
				printf ("ray.sideDist.x < ray.sideDist.y\n");
				printf ("ray.map_coord.x :	(%d ; %d)\n", ray.map_coord.x, ray.map_coord.y);
				printf ("ray.sideDist :		(%f ; %f)\n", ray.sideDist.x, ray.sideDist.y);
			}	
		}
		else
		{
			ray.sideDist.y += itrsec_dist.y;
			ray.map_coord.y += step.y;
			ray.side = 1;
			ray.wallHit = ray.ray_dir.y > 0 ? 3 : 1;
			if (ray.ray_dir.y == 0 && ray.ray_dir.x == -1)
			{
				printf ("ray.sideDist.x > ray.sideDist.y\n");
				printf ("ray.map_coord.x :	(%d ; %d)\n", ray.map_coord.x, ray.map_coord.y);
				printf ("ray.sideDist :		(%f ; %f)\n", ray.sideDist.x, ray.sideDist.y);
			}	

		}
		if (ray.map_coord.x >= l->size.x || ray.map_coord.x < 0
		 || ray.map_coord.y >= l->size.y || ray.map_coord.y < 0)
		{

			ray.hit = 0;
			ray.type = 0;
			return (ray);
		}
		if (l->c[ray.map_coord.x][ray.map_coord.y].w_id[ray.wallHit] != 0)
		{
			if (ray.ray_dir.y == 0 && ray.ray_dir.x == -1)
			{
				printf ("\nFinal\n");
				printf ("ray.map_coord.x :	(%d ; %d)\n", ray.map_coord.x, ray.map_coord.y);
				printf ("ray.sideDist :		(%f ; %f)\n", ray.sideDist.x, ray.sideDist.y);
				printf ("hit at %d %d wall %d\n", ray.map_coord.y, ray.map_coord.x, ray.wallHit);
			}	
			ray.type = l->c[ray.map_coord.y][ray.map_coord.x].w_id[ray.wallHit];
			ray.hit = 1;
		}
		s++;
		/*
		if (l->tab[ray.map_coord.y][ray.map_coord.x][0] != '0')
		{
			ray.hit = 1;
			ray.type = l->tab[ray.map_coord.y][ray.map_coord.x][0];
		}
		*/
	}
	return (ray);
}

static	t_ray	calc_dist(t_vector2f p, t_ray ray, t_vector2i step)
{
	if (!ray.side)
	{

		ray.dist = (ray.map_coord.x - p.x + (1 - step.x) / 2) / ray.ray_dir.x;
	//printf("ray lenght : %f\n", ray.dist);/*
	}
	else
	{
		ray.dist = (ray.map_coord.y - p.y + (1 - step.y) / 2) / ray.ray_dir.y;
		/*if (ray.wallHit == 1)
			ray.dist -= 1;
		else
			ray.dist += 1;*/
	}
	return (ray);
}

// old 
//t_ray				cast_ray(t_player	*p, t_level	*l, int x, int size)
t_ray				cast_ray(t_player	*p, t_map	*l, int x, int size)
{
	t_ray		ray;
	double		cam_x;
	t_vector2i 	step;
	t_vector2d	itrsec_dist;

	cam_x = 2 * x / (double)size - 1;
	ray.ray_dir = (t_vector2d){	p->dir.x + p->canvas_plane.x * cam_x,
								p->dir.y + p->canvas_plane.y * cam_x};
	ray.map_coord = (t_vector2i){(int)p->pos.x, (int)p->pos.y};
	itrsec_dist = (t_vector2d){fabs(1 / ray.ray_dir.x), fabs(1/ray.ray_dir.y)};
	step.x = ray.ray_dir.x < 0 ? -1 : 1;
	step.y = ray.ray_dir.y < 0 ? -1 : 1;
	if (ray.ray_dir.x < 0)
		ray.sideDist.x = (p->pos.x - ray.map_coord.x) * itrsec_dist.x;
	else
		ray.sideDist.x = (ray.map_coord.x + 1.0 - p->pos.x) * itrsec_dist.x;
	if (ray.ray_dir.y < 0)
		ray.sideDist.y = (p->pos.y - ray.map_coord.y) * itrsec_dist.y;
	else
		ray.sideDist.y = (ray.map_coord.y + 1.0 - p->pos.y) * itrsec_dist.y;
	//printf("test\n");
	ray = raycast_dda(l, ray, itrsec_dist, step);
	ray = calc_dist(p->pos, ray, step);
	//printf("Dist : %f\n", ray.dist);
	//printf("ray : dist : %f, hit : %d, side : %d c\n", ray.dist, ray.hit, ray.side);
	return (ray);
}

/*
static t_vector2f		vertical_check(t_vector2f srt, float angle, t_level *lvl)
{
	t_vector2f 	a;
	t_vector2f	itrsc;
	float		rad;
	int			found;

	rad = degreesToRadians(angle);
	itrsc.x = floorf(srt.x) + 1;
	itrsc.y = srt.y + ((srt.x - itrsc.x) * tanf(rad));
	a.x = angle <= 90 || angle >= 270 ? 1 : -1;
	a.y = -tanf(rad);
	//printf("a        : {%f,%f}\n", a.x, a.y);
	found = 0;
	while (!found)
	{
		//printf("itrsc    : {%f,%f}\n", itrsc.x, itrsc.y);
		//printf("itrsc rd : {%f,%f}\n", floorf(itrsc.x), floorf(itrsc.y));
		if (itrsc.x < 0 || itrsc.y < 0
			|| itrsc.x > (float)lvl->width - 1 || itrsc.y > (float)lvl->height - 1)
		{
			found = 1;
			itrsc = (t_vector2f){-1.0, -1.0};
		}
		else if (lvl->tab[(int)roundf(itrsc.y)][(int)roundf(itrsc.x)][0] != '0')
		{
			found = 1;
			//itrsc = (t_vector2f){-1.0, -1.0};
		}
		else
		{
			itrsc.x += a.x;
			itrsc.y += a.y;
		}
	}
	return (itrsc);
}

static t_vector2f		horizontal_check(t_vector2f srt, float angle, t_level *lvl)
{
	t_vector2f 	a;
	t_vector2f	itrsc;
	float		rad;
	int			found;

	rad = degreesToRadians(angle);
	a.y = angle >= 0 && angle <= 180 ? - 1 : 1;
	a.x = 1.0 / tanf(rad);
	itrsc.y = roundf(srt.y) + a.y;
	itrsc.x = srt.x + ((srt.y - itrsc.y) / tanf(rad));
	found = 0;
	//printf("a        : {%f,%f}\n", a.x, a.y);
	//printf("width height %f %f\n", (float)lvl->width, (float)lvl->height);
	while (!found)
	{
		if (floorf(angle) == 65)
		{
			//printf("itrsc    : {%f,%f}\n", itrsc.x, itrsc.y);
			//printf("itrsc fl : {%f,%f}\n", floorf(itrsc.x), floorf(itrsc.y));
			//printf("itrsc rd : {%f,%f}\n\n", roundf(itrsc.x), roundf(itrsc.y));

		}
		if (itrsc.x < 0 || itrsc.y < 0
		|| itrsc.x > (float)lvl->width - 1 || itrsc.y > (float)lvl->height - 1)
		{
			found = 1;
			itrsc = (t_vector2f){-1.0, -1.0};
		}
		else if (lvl->tab[(int)roundf(itrsc.y)][(int)roundf(itrsc.x)][0] != '0')
		{
			found = 1;
			//itrsc = (t_vector2f){-1.0, -1.0};
		}
		else
		{
			itrsc.x += a.x;
			itrsc.y += a.y;
		}
	}
	if (floorf(angle) == 65)
		{
			//printf("--------------\n");
		}
	return (itrsc);
}

float				cast_ray(t_vector2f srt, float angle, t_level	*level)
{
	t_vector2f	itrsc;
	t_vector2f	dist;
	float		rad;

	rad = degreesToRadians(angle);
	//printf("angle    : %f\n", angle);
	//printf("rad      : %f\n", rad);
	//printf("cos(rad) : %Lf\n", sinf(rad));
	itrsc = horizontal_check(srt, angle, level);
	//printf("Intersection {%f,%f}\n", itrsc.x, itrsc.y);
	if (itrsc.x != -1)
		dist.x = sqrtf(powf(srt.x - itrsc.x, 2) + powf(srt.y - itrsc.y, 2));
	else
		dist.x = -1;
	itrsc = vertical_check(srt, angle, level);
	//printf("Intersection {%f,%f}\n", itrsc.x, itrsc.y);
	if (itrsc.y != -1)
		dist.y = sqrtf(powf(srt.x - itrsc.x, 2) + powf(srt.y - itrsc.y, 2));
		//dist.y = fabs(srt.x - itrsc.x) / cosf(rad);
	else
		dist.y = -1;
	//printf("Hor dist ; Ver dist {%f,%f}\n", dist.x, dist.y);
	if (dist.x == -1 && dist.y == -1)
	{
		//printf("Detection failed with %f degrees\n", angle);
	}
	if (dist.x == -1)
		return (dist.y);
	else if (dist.y == -1)
		return (dist.x);
	else
	{
		return (dist.x < dist.y ? dist.x : dist.y);
	}
}
*/
/**
 * Gerer le centre
 **/