/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <nbuhler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:36:50 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/26 19:01:10 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	cal_side_dist(t_ray *ray)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidedx = (ray->posx - ray->mapx) * ray->ddistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedx = (ray->mapx + 1.0 - ray->posx) * ray->ddistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->sidedy = (ray->posy - ray->mapy) * ray->ddisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedy = (ray->mapy + 1.0 - ray->posy) * ray->ddisty;
	}
}

static void	hit_wall(t_env *e, t_ray *ray)
{
	while (1)
	{
		if (ray->sidedx < ray->sidedy)
		{
			ray->sidedx += ray->ddistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedy += ray->ddisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (e->map[ray->mapy][ray->mapx] > 0)
			break ;
	}
}

static void	cal_dist_ray_to_perpwall(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->walldist = (ray->mapx - ray->posx + (1 - ray->stepx) / 2)
		/ ray->dirx;
	}
	else
	{
		ray->walldist = (ray->mapy - ray->posy + (1 - ray->stepy) / 2)
		/ ray->diry;
	}
}

static void	cal_draw_start_end(t_ray *ray)
{
	int line_height;

	line_height = (int)(WIN_H / ray->walldist);
	ray->draw_start = -line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

void		raycasting(t_env *e)
{
	int		x;
	t_ray	ray;

	draw_map(e);
	ray.posx = e->player_posx;
	ray.posy = e->player_posy;
	x = -1;
	while (++x < WIN_W)
	{
		ray.camerax = (2 * x) / (double)WIN_W - 1;
		ray.dirx = e->player_dirx + e->planex * ray.camerax;
		ray.diry = e->player_diry + e->planey * ray.camerax;
		ray.mapx = (int)ray.posx;
		ray.mapy = (int)ray.posy;
		ray.ddistx = sqrt(1 + pow(ray.diry, 2) / pow(ray.dirx, 2));
		ray.ddisty = sqrt(1 + pow(ray.dirx, 2) / pow(ray.diry, 2));
		cal_side_dist(&ray);
		hit_wall(e, &ray);
		cal_dist_ray_to_perpwall(&ray);
		cal_draw_start_end(&ray);
		draw_line(e, &ray, x);
	}
	draw_player_dir(e);
}
