/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:22:13 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/27 14:07:09 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	draw_ray_x(t_env *e, t_draw draw)
{
	int cumul;
	int	i;
	int x;
	int y;

	i = 1;
	x = draw.xi;
	y = draw.yi;
	cumul = draw.dx / 2;
	while (i <= draw.dx)
	{
		x += draw.xinc;
		if ((cumul += draw.dy) >= draw.dx)
		{
			cumul -= draw.dx;
			y += draw.yinc;
		}
		fill_pixel(&e->pxl, x, y, draw.color);
		i++;
	}
}

static void	draw_ray_y(t_env *e, t_draw draw)
{
	int cumul;
	int	i;
	int x;
	int y;

	i = 1;
	x = draw.xi;
	y = draw.yi;
	cumul = draw.dy / 2;
	while (i <= (int)draw.dy)
	{
		y += draw.yinc;
		if ((cumul += draw.dx) >= draw.dy)
		{
			cumul -= draw.dy;
			x += draw.xinc;
		}
		fill_pixel(&e->pxl, x, y, draw.color);
		i++;
	}
}

void		draw_ray(t_env *e, double xf, double yf, int color)
{
	t_draw	draw;
	int		decalx;

	decalx = WIN_W - MINI_MAPW;
	draw.xf = xf * (double)(MINI_MAPW / SQUARE_MAP_SIZE) + decalx;
	draw.yf = yf * (double)(MINI_MAPH / SQUARE_MAP_SIZE);
	draw.xi = e->player_posx * (double)(MINI_MAPW / SQUARE_MAP_SIZE) + decalx;
	draw.yi = e->player_posy * (double)(MINI_MAPH / SQUARE_MAP_SIZE);
	draw.dx = draw.xf - draw.xi;
	draw.dy = draw.yf - draw.yi;
	draw.xinc = draw.dx > 0 ? 1 : -1;
	draw.yinc = draw.dy > 0 ? 1 : -1;
	draw.dx = abs(draw.dx);
	draw.dy = abs(draw.dy);
	draw.color = color;
	fill_pixel(&e->pxl, draw.xi, draw.yi, draw.color);
	if (draw.dx > draw.dy)
		draw_ray_x(e, draw);
	else
		draw_ray_y(e, draw);
}
