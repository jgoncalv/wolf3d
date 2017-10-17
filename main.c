/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 19:23:21 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/16 19:23:23 by nbuhler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pxl(t_env *e, int x, int y, unsigned int c)
{
	int	i;

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
	while(i++ < e->height)
		put_pxl(e,x,i,e->color2);

}

void ft_init_player(t_env *e)
{
	e->player.posX = 1;
	e->player.posY = 1;
	e->player.dirX = -1;
	e->player.dirY = 0;
	e->player.planeX = 0;
	e->player.planeY = 0.66;
}

void ft_init_ray(t_env *e)
{
	e->ray.ray_posX = 0;
	e->ray.ray_posY = 0;
	e->ray.cameraX = 0;
	e->ray.ray_dirX = 0;
	e->ray.ray_dirY = 0;
	e->ray.side_distX = 0;
	e->ray.side_distY = 0;
	e->ray.delta_distX = 0;
	e->ray.delta_distY = 0;
	e->ray.perp_wallDist = 0;
	e->ray.stepX = 0;
	e->ray.stepY = 0;
	e->ray.hit = 0;
	e->ray.side = 0;
	e->ray.lineHeight = 0;
	e->ray.drawStart = 0;
	e->ray.drawEnd = 0;

}

int  **ft_init_map(t_env *e)//, int fd, char *map)
{
	int tt[3][3] = {
		{1,1,1},
		{1,0,1},
		{1,1,1},
	 };
	e->map.mapX = 0;
	e->map.mapY = 0;
	e->map.map = tt;
	return tt;
}


t_env ft_init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->width = 800;
	e->height = 600;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->width, e->height, "Wolf3D");
	e->img = mlx_new_image(e->mlx, e->width, e->height);
	e->pxl = mlx_get_data_addr(e->img, &(e->bpp), &(e->s_line), &(e->ed));
	e->colorsky = 0x00cdff;
	e->color = 0xff9600;
	e->color2 = 0x73ff00;
	ft_init_player(e);
	ft_init_ray(e);
	ft_init_map(e);
	return *e;
}


void raycasting(t_env *e)
{
	int x;

	x = -1;
	while(x < e->width)
			{
				e->ray.cameraX = (2 * x) / e->width - 1;
				e->ray.ray_posX = e->player.posX;
				e->ray.ray_posY = e->player.posY;
				e->ray.ray_dirX = e->player.dirX + e->player.planeX * e->ray.cameraX;
				e->ray.ray_dirY = e->player.dirY + e->player.planeY * e->ray.cameraX;

				e->map.mapX = e->ray.ray_posX;
				e->map.mapY = e->ray.ray_posY;
				e->ray.delta_distX = sqrt(1 + (e->ray.ray_dirY * e->ray.ray_dirY) / (e->ray.ray_dirX * e->ray.ray_dirX));
				e->ray.delta_distY = sqrt(1 + (e->ray.ray_dirX * e->ray.ray_dirX) / (e->ray.ray_dirY * e->ray.ray_dirY));
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
					e->ray.side_distX = (e->map.mapY + 1.0 - e->ray.ray_posY) * e->ray.delta_distY;	
				}
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
						e->map.mapX += e->ray.stepX;
						e->ray.side = 1;	
					}
					if(e->map.map[e->map.mapX][e->map.mapY] > 0)
						e->ray.hit = 1;
				}
				if(e->ray.side == 0)
					e->ray.perp_wallDist = (e->map.mapX - e->ray.ray_posX + (1 - e->ray.stepX) / 2) / e->ray.ray_dirX;
				else
					e->ray.perp_wallDist = (e->map.mapY - e->ray.ray_posY + (1 - e->ray.stepY) / 2) / e->ray.ray_dirY;
				e->ray.lineHeight = e->height / e->ray.perp_wallDist;
				e->ray.drawStart = -e->ray.lineHeight / 2 + e->height / 2;
				if(e->ray.drawStart < 0)
					e->ray.drawStart = 0;
				e->ray.drawEnd = e->ray.lineHeight / 2 + e->height / 2;
				if(e->ray.drawEnd >= e->height)
					e->ray.drawEnd = e->height - 1;
				draw_line(e, x);
			}	
}


int main(int argc, char **argv)
{
	t_env e;
	char *str;

	if(argc != 2)
	{
		return (0);
	}
	else
	{	
		str = argv[1];
		e = ft_init_env(&e);
		raycasting(&e);
		mlx_loop(e.mlx);
	}	

	return 0;
}