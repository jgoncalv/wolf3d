/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <nbuhler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:36:50 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/25 18:17:30 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void cal_side_dist(t_ray *ray)
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

static void hit_wall(t_env *e, t_ray *ray)
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

static void cal_dist_ray_to_perpwall(t_ray *ray)
{
	if (ray->side == 0)
		ray->walldist = (ray->mapx - ray->posx + (1 - ray->stepx) / 2) / ray->dirx;
    else
    	ray->walldist = (ray->mapy - ray->posy + (1 - ray->stepy) / 2) / ray->diry;
}

static void cal_draw_start_end(t_ray *ray)
{
	int line_height;

	line_height = (int)(WIN_H / ray->walldist);
	  ray->draw_start = -line_height / 2 + WIN_H / 2;
	  if(ray->draw_start < 0)
	  	ray->draw_start = 0;
	  ray->draw_end = line_height / 2 + WIN_H / 2;
	  if(ray->draw_end >= WIN_H)
	  	ray->draw_end = WIN_H - 1;
}

void    put_pxl(t_env *e, int x, int y, unsigned int c)
{
	int    i;

	if (x >= (WIN_W - MINI_MAPW) && y <= (MINI_MAPH))
		return ;

	i = (x * 4) + (y * e->s_line);
	e->pxl[i] = c;
	e->pxl[++i] = c >> 8;
	e->pxl[++i] = c >> 16;
}

void draw_line(t_env *e, t_ray *ray, int x)
{
	int i;

	i = -1;
	while(++i < ray->draw_start)
		put_pxl(e,x,i,e->colorsky);
	i--;
	while(++i <= ray->draw_end && i < WIN_H)
		put_pxl(e,x,i,e->color1);
	i--;
	while(++i < WIN_H)
		put_pxl(e,x,i,e->color2);
}


void	fill_pixel(char **img, int x, int y, int color)
{
	if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
	{
		((int*)*img)[x + (y * WIN_W)] = color;
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

	// draw player pos
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

	//printf("diry= %f, dirx= %f rayy= %f rayx %f\n", e->player_diry, e->player_dirx, rayy, rayx);

	draw_ray(e, rayx, rayy, 0x00ff00);
}

void	raycasting(t_env *e)
{
	int		x;
	t_ray	ray;

	draw_map(e);
	ray.posx = e->player_posx;
	ray.posy = e->player_posy;
	x = -1;
	while(++x < WIN_W)
	{
		ray.camerax = (2 * x) / (double)WIN_W - 1;
		ray.dirx = e->player_dirx + e->planex * ray.camerax;
		ray.diry = e->player_diry + e->planey * ray.camerax;
		ray.mapx = (int)ray.posx;
		ray.mapy = (int)ray.posy;
		ray.ddistx = sqrt(1 + pow(ray.diry,2) / pow(ray.dirx, 2));
		ray.ddisty = sqrt(1 + pow(ray.dirx,2) / pow(ray.diry, 2));
		//printf("%f %f %f %f\n", pow(ray.diry,2), pow(ray.dirx,2), ray.ddistx, ray.ddisty);
		cal_side_dist(&ray);
		hit_wall(e, &ray);
		cal_dist_ray_to_perpwall(&ray);
		cal_draw_start_end(&ray);
		draw_line(e,&ray,x);
		//draw_ray(e, ray.sidedx, ray.sidedy, 0xff0000);
	}
	draw_player_dir(e);
}
