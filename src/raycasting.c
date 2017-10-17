/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 18:29:01 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/17 18:52:54 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	init_ray_pos(double x, t_env *e)
{
		e->ray.cameraX = (2 * x) / (double)e->width - 1;
		e->ray.ray_posX = e->player.posX;
		e->ray.ray_posY = e->player.posY;
		e->ray.ray_dirX = e->player.dirX + e->player.planeX * e->ray.cameraX;
		e->ray.ray_dirY = e->player.dirY + e->player.planeY * e->ray.cameraX;

		e->map.mapX = e->ray.ray_posX;
		e->map.mapY = e->ray.ray_posY;
		e->ray.delta_distX = sqrt(1 + (e->ray.ray_dirY * e->ray.ray_dirY) / (e->ray.ray_dirX * e->ray.ray_dirX));
		e->ray.delta_distY = sqrt(1 + (e->ray.ray_dirX * e->ray.ray_dirX) / (e->ray.ray_dirY * e->ray.ray_dirY));
}

static void	init_dist(t_env *e)
{
	if(e->ray.ray_dirX < 0)
	{
		e->ray.stepX = -1;
		e->ray.side_distX = (e->ray.ray_posX - e->map.mapX) * e->ray.delta_distX;
	}
	else
	{
		e->ray.stepX = 1;
		e->ray.side_distX = (e->map.mapX + 1.0 - e->ray.ray_posX) * e->ray.delta_distX;
	}
	if(e->ray.ray_dirY < 0)
	{
		e->ray.stepY = -1;
		e->ray.side_distY = (e->ray.ray_posY - e->map.mapY) * e->ray.delta_distY;
	}
	else
	{
		e->ray.stepY = 1;
		e->ray.side_distY = (e->map.mapY + 1.0 - e->ray.ray_posY) * e->ray.delta_distY;
	}
}

static void	init_side(t_env *e)
{
	while(e->ray.hit == 1)
	{
		if(e->ray.side_distX < e->ray.side_distY)
		{
			e->ray.side_distX += e->ray.delta_distX;
			e->map.mapX += e->ray.stepX;
			e->ray.side = 0;
		}
		else
		{
			e->ray.side_distY += e->ray.delta_distY;
			e->map.mapY += e->ray.stepY;
			e->ray.side = 1;
		}
		if(e->map.map[e->map.mapX][e->map.mapY] > 0)
			e->ray.hit = 1;
	}
}

static void	init_draw(t_env *e)
{
	if(e->ray.side == 0)
		e->ray.perp_wallDist = (e->map.mapX - e->ray.ray_posX + (1 - (double)e->ray.stepX) / 2) / e->ray.ray_dirX;
	else
		e->ray.perp_wallDist = (e->map.mapY - e->ray.ray_posY + (1 - (double)e->ray.stepY) / 2) / e->ray.ray_dirY;
	e->ray.lineHeight = (int)((double)e->height / e->ray.perp_wallDist);

	e->ray.drawStart = -e->ray.lineHeight / 2 + e->height / 2;
	if(e->ray.drawStart < 0)
		e->ray.drawStart = 0;
	e->ray.drawEnd = e->ray.lineHeight / 2 + e->height / 2;
	if(e->ray.drawEnd >= e->height)
		e->ray.drawEnd = e->height - 1;
}

void    put_pxl(t_env *e, int x, int y, unsigned int c)
{
	int    i;

	i = (x * 4) + (y * e->s_line);
	e->pxl[i] = c;
	e->pxl[++i] = c >> 8;
	e->pxl[++i] = c >> 16;
}

void draw_line(t_env *e, int x)
{
	int i;

	i = -1;
	while(++i < e->ray.drawStart)
		put_pxl(e,x,i,e->colorsky);
	i--;
	while(++i <= e->ray.drawEnd && i < e->height)
		put_pxl(e,x,i,e->color);
	i--;
	while(++i < e->height)
		put_pxl(e,x,i,e->color2);
}

void raycasting(t_env *e)
{
	int x;

	x = -1;
	while(++x < e->width)
	{
		init_ray_pos(x, e);
		init_dist(e);
		init_side(e);
		init_draw(e);
		draw_line(e, x);
	}
}
