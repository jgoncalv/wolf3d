/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loophook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <nbuhler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:43:36 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/26 19:19:49 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_up(t_env *e)
{
	int x;
	int y;

	x = (int)(e->player_posx + e->player_dirx * MV_SPEED);
	y = (int)(e->player_posy);
	if (e->map[y][x] == 0)
		e->player_posx += e->player_dirx * MV_SPEED;
	x = (int)(e->player_posx);
	y = (int)(e->player_posy + e->player_diry * MV_SPEED);
	if (e->map[y][x] == 0)
		e->player_posy += e->player_diry * MV_SPEED;
}

void	move_down(t_env *e)
{
	int x;
	int y;

	x = (int)(e->player_posx - e->player_dirx * MV_SPEED);
	y = (int)(e->player_posy);
	if (e->map[y][x] == 0)
		e->player_posx -= e->player_dirx * MV_SPEED;
	x = (int)(e->player_posx);
	y = (int)(e->player_posy - e->player_diry * MV_SPEED);
	if (e->map[y][x] == 0)
		e->player_posy -= e->player_diry * MV_SPEED;
}

void	move_right(t_env *e)
{
	double old_dirx;
	double old_planex;

	old_dirx = e->player_dirx;
	old_planex = e->planex;
	e->player_dirx = e->player_dirx * cos(-ROT_SPEED) -
	e->player_diry * sin(-ROT_SPEED);
	e->player_diry = old_dirx * sin(-ROT_SPEED) +
	e->player_diry * cos(-ROT_SPEED);
	e->planex = e->planex * cos(-ROT_SPEED) - e->planey * sin(-ROT_SPEED);
	e->planey = old_planex * sin(-ROT_SPEED) + e->planey * cos(-ROT_SPEED);
}

void	move_left(t_env *e)
{
	double old_dirx;
	double old_planex;

	old_dirx = e->player_dirx;
	old_planex = e->planex;
	e->player_dirx = e->player_dirx * cos(ROT_SPEED) -
	e->player_diry * sin(ROT_SPEED);
	e->player_diry = old_dirx * sin(ROT_SPEED) +
	e->player_diry * cos(ROT_SPEED);
	e->planex = e->planex * cos(ROT_SPEED) - e->planey * sin(ROT_SPEED);
	e->planey = old_planex * sin(ROT_SPEED) + e->planey * cos(ROT_SPEED);
}

int		loop_hook(t_env *e)
{
	if (e->player_move_up)
		move_up(e);
	if (e->player_move_down)
		move_down(e);
	if (e->player_move_right)
		move_right(e);
	if (e->player_move_left)
		move_left(e);
	raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
