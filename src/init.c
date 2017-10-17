/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:44:06 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/17 16:54:00 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void ft_init_player(t_env *e, char **map)
{
	int x;
	int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				break ;
			x++;
		}
		if (map[y][x] && map[y][x] == '0')
			break ;
		y++;
	}
	e->player.posX = x;
	e->player.posY = y;
	e->player.dirX = -1;
	e->player.dirY = 0;
	e->player.planeX = 0;
	e->player.planeY = 0.66;
}

static void ft_init_ray(t_env *e)
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

static void ft_init_map(t_env *e, char **map)
{
	int **new;
	int *newi;
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	e->map.mapX = 0;
	e->map.mapY = 0;
	e->map.map_l = ft_tablen(map);
	e->map.map_w = ft_strlen(*map);
	new = (int **)malloc(sizeof(int *) * e->map.map_l);
	newi = (int *)malloc(sizeof(int) * (e->map.map_l * e->map.map_w));
	if (!new || !newi)
		error_message();
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			newi[k] = (int)(map[i][j] - '0');
			k++;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < e->map.map_l)
	{
		new[i] = &(newi[i * e->map.map_w]);
		i++;
	}
	e->map.map = new;
}


t_env init(char **map)
{
	t_env e;

	ft_bzero(&e, sizeof(t_env));
	e.width = 800;
	e.height = 600;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.width, e.height, "Wolf3D");
	e.img = mlx_new_image(e.mlx, e.width, e.height);
	e.pxl = mlx_get_data_addr(e.img, &(e.bpp), &(e.s_line), &(e.ed));
	e.colorsky = 0x00cdff;
	e.color = 0xff9600;
	e.color2 = 0x73ff00;
	ft_init_player(&e, map);
	ft_init_ray(&e);
	ft_init_map(&e, map);
	return (e);
}
