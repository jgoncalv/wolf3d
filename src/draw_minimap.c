/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <nbuhler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:21:12 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/27 14:10:40 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_player_dir(t_env *e)
{
	double rayx;
	double rayy;

	rayx = e->player_posx + e->player_dirx;
	rayy = e->player_posy + e->player_diry;
	draw_ray(e, rayx, rayy, 0x00ff00);
}

static void	draw_map2(t_env *e, int x, int y)
{
	int player_size;
	int decalx;
	int ymax;
	int xmax;

	player_size = 2;
	decalx = WIN_W - MINI_MAPW;
	ymax = e->player_posy * (MINI_MAPH / SQUARE_MAP_SIZE) + player_size;
	y = e->player_posy * (MINI_MAPH / SQUARE_MAP_SIZE) - player_size;
	xmax = e->player_posx * (MINI_MAPW / SQUARE_MAP_SIZE) +
		player_size + decalx;
	while (y < ymax)
	{
		x = e->player_posx * (MINI_MAPW / SQUARE_MAP_SIZE) -
			player_size + decalx;
		while (x < xmax)
		{
			fill_pixel(&e->pxl, x, y, 0xff0000);
			x++;
		}
		y++;
	}
}

void		draw_map(t_env *e)
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
	draw_map2(e, x, y);
}
