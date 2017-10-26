/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:46:12 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/25 15:46:19 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


int get_color(t_env *e, t_ray *ray)
{
	if (ray->side == 1)
	{
		if ((ray->stepx == -1 && ray->stepy == -1) || (ray->stepx == 1 && ray->stepy == -1))
			return (e->color_east);
		if ((ray->stepx == -1 && ray->stepy == 1) || (ray->stepx == 1 && ray->stepy == 1))
			return (e->color_west);
	}
	if ((ray->stepx == -1 && ray->stepy == -1) || (ray->stepx == -1 && ray->stepy == 1))
		return (e->color_north);
	return (e->color_south);

}

int smog(double d, int color)
{
	int	r;
	int	g;
	int	b;

	r = color / 256 / 256;
	g = color / 256 % 256;
	b = color % 256;
	if (r > 0)
		r = r - ((r * d) / SMOG_DIST);
	if (g > 0)
		g = g - ((g * d) / SMOG_DIST);
	if (b > 0)
		b = b - ((b * d) / SMOG_DIST);
	r = r <= 0 || r > 255 ? 0 : r;
	g = g <= 0 || g > 255 ? 0 : g;
	b = b <= 0 || b > 255 ? 0 : b;
	color = (r * 256 * 256) + (g * 256) + b;
	return (color);
}

void draw_line(t_env *e, t_ray *ray, int x)
{
	int		i;
	double	init;
	double	d;

	i = -1;
	init = (WIN_H - 1) / (SQUARE_MAP_SIZE - 1);
	while(++i < ray->draw_start)
	{
		d = (double)i / init;
		d = d < 0 ? d * -1 : d;
		put_pxl(e, x, i, smog(d, e->colorsky));
	}
	i--;
	while(++i <= ray->draw_end && i < WIN_H)
		put_pxl(e, x, i, smog(ray->walldist, get_color(e, ray)));
	i--;
	while(++i < WIN_H)
	{
		d = (SQUARE_MAP_SIZE - 1) - (double)i / init;
		d = d < 0 ? d * -1 : d;
		put_pxl(e, x, i, smog(d, e->colorground));
	}
}

void draw_map(t_env *e)
{
	int i;
	int j;
	int x;
	int y;

	i = -1;
	while (++i < MINI_MAPH)
	{
		j = WIN_W - MINI_MAPW - 1;
		while (++j < WIN_W)
		{
			x = (j - (WIN_W - MINI_MAPW)) / (MINI_MAPW / SQUARE_MAP_SIZE);
			y = i / (MINI_MAPH / SQUARE_MAP_SIZE);
			if (e->map[y][x] == 0)
				fill_pixel(&e->pxl, j, i, 0xFFFFFF);
			else
				fill_pixel(&e->pxl, j, i, 0x000000);
		}
	}

	int player_size = 2;
	int decalx = WIN_W - MINI_MAPW;
	int ymax = e->player_posy * (MINI_MAPH / SQUARE_MAP_SIZE) + player_size;
	int xmax = e->player_posx * (MINI_MAPW / SQUARE_MAP_SIZE) + player_size + decalx;
	y = e->player_posy * (MINI_MAPH / SQUARE_MAP_SIZE) - player_size;
	while (y < ymax)
	{
		x = e->player_posx * (MINI_MAPW / SQUARE_MAP_SIZE) - player_size + decalx;
		while (x < xmax)
		{
			fill_pixel(&e->pxl, x, y, 0xff0000);
			x++;
		}
		y++;
	}
}

void draw_player_dir(t_env *e)
{
	double rayx = e->player_posx + (e->player_dirx * 1.5);
	double rayy = e->player_posy + (e->player_diry * 1.5);

	draw_ray(e, rayx, rayy, 0x00ff00);
}