/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:44:06 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/27 15:32:53 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_init_player(t_env *e, char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
				break ;
		}
		if (map[y][x] && map[y][x] == '0')
			break ;
	}
	e->player_posx = x + 0.5;
	e->player_posy = y + 0.5;
	e->player_dirx = 0;
	e->player_diry = 1;
	e->planex = 0.66;
	e->planey = 0;
	e->player_move_up = 0;
	e->player_move_down = 0;
	e->player_move_right = 0;
	e->player_move_left = 0;
}

static void	ft_init_map(t_env *e, char **map)
{
	int i;
	int j;

	i = 0;
	e->mapx = 0;
	e->mapy = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			e->map[i][j] = (int)(map[i][j] - '0');
			j++;
		}
		i++;
	}
}

t_env		init(char **map)
{
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	e.width = WIN_W;
	e.height = WIN_H;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.width, e.height, "Wolf3D");
	e.img = mlx_new_image(e.mlx, e.width, e.height);
	e.pxl = mlx_get_data_addr(e.img, &(e.bpp), &(e.s_line), &(e.ed));
	e.colorsky = 0x065a69;
	e.colorground = 0x340707;
	e.color_east = 0x8b2c2c;
	e.color_west = 0xdb551b;
	e.color_north = 0x362121;
	e.color_south = 0x877979;
	ft_init_player(&e, map);
	ft_init_map(&e, map);
	return (e);
}
