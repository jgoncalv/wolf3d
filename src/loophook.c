/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loophook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:43:36 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/25 19:43:43 by nbuhler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_up(t_env *e)
{		
	double moveSpeed = 0.03;

	if(e->map[(int)(e->player_posy)][(int)(e->player_posx + e->player_dirx * moveSpeed)] == 0)
		e->player_posx += e->player_dirx * moveSpeed;
	if(e->map[(int)(e->player_posy + e->player_diry * moveSpeed)][(int)(e->player_posx)] == 0)
		e->player_posy += e->player_diry * moveSpeed;
}

void	move_down(t_env *e)
{
	double moveSpeed = 0.03;

	if(e->map[(int)(e->player_posy)][(int)(e->player_posx - e->player_dirx * moveSpeed)] == 0)
		e->player_posx -= e->player_dirx * moveSpeed;
	if(e->map[(int)(e->player_posy - e->player_diry * moveSpeed)][(int)(e->player_posx)] == 0)
		e->player_posy -= e->player_diry * moveSpeed;
}

void	move_right(t_env *e)
{
	double oldDirX = e->player_dirx;
	double oldPlaneX = e->planex;
	double rotSpeed = 0.03;

	e->player_dirx = e->player_dirx * cos(-rotSpeed) - e->player_diry * sin(-rotSpeed);
	e->player_diry = oldDirX * sin(-rotSpeed) + e->player_diry * cos(-rotSpeed);
	e->planex = e->planex * cos(-rotSpeed) - e->planey * sin(-rotSpeed);
	e->planey = oldPlaneX * sin(-rotSpeed) + e->planey * cos(-rotSpeed);
}

void	move_left(t_env *e)
{
	double oldDirX = e->player_dirx;
	double oldPlaneX = e->planex;
	double rotSpeed = 0.03;
	
	e->player_dirx = e->player_dirx * cos(rotSpeed) - e->player_diry * sin(rotSpeed);
	e->player_diry = oldDirX * sin(rotSpeed) + e->player_diry * cos(rotSpeed);
	e->planex = e->planex * cos(rotSpeed) - e->planey * sin(rotSpeed);
	e->planey = oldPlaneX * sin(rotSpeed) + e->planey * cos(rotSpeed);
}

int		loop_hook(t_env *e)
{
	if(e->player_move_up)
		move_up(e);
	if(e->player_move_down)
		move_down(e);
	if(e->player_move_right)
		move_right(e);
	if(e->player_move_left)
		move_left(e);
	raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return 0;
}
