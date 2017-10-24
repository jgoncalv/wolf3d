/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:10:02 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/24 19:10:03 by nbuhler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			keyhook(int keycode, t_env *e)
{
	double moveSpeed = 0.1;
	double rotSpeed = 0.1;

	printf("%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_image(e->mlx, e->img);
		mlx_clear_window(e->mlx, e->win);
		exit(0);
	}
	if (keycode == UP_ARROW)
	{
		if(e->map[(int)(e->player_posx + e->player_dirx * moveSpeed)][(int)(e->player_posy)] == 0)
			e->player_posx += e->player_dirx * moveSpeed;
		if(e->map[(int)(e->player_posx)][(int)(e->player_posy + e->player_diry * moveSpeed)] == 0)
			e->player_posy += e->player_diry * moveSpeed;
	}
	else if (keycode == DOWN_ARROW)
	{
		if(e->map[(int)(e->player_posx - e->player_dirx * moveSpeed)][(int)(e->player_posy)] == 0)
			e->player_posx -= e->player_dirx * moveSpeed;
		if(e->map[(int)(e->player_posx)][(int)(e->player_posy - e->player_diry * moveSpeed)] == 0)
			e->player_posy -= e->player_diry * moveSpeed;
	}
	else if (keycode == RIGHT_ARROW)
	{
		double oldDirX = e->player_dirx;
		e->player_dirx = e->player_dirx * cos(-rotSpeed) - e->player_diry * sin(-rotSpeed);
		e->player_diry = oldDirX * sin(-rotSpeed) + e->player_diry * cos(-rotSpeed);
		double oldPlaneX = e->planex;
		e->planex = e->planex * cos(-rotSpeed) - e->planey * sin(-rotSpeed);
		e->planey = oldPlaneX * sin(-rotSpeed) + e->planey * cos(-rotSpeed);
	}
	else if (keycode == LEFT_ARROW)
	{
		double oldDirX = e->player_dirx;
		e->player_dirx = e->player_dirx * cos(rotSpeed) - e->player_diry * sin(rotSpeed);
		e->player_diry = oldDirX * sin(rotSpeed) + e->player_diry * cos(rotSpeed);
		double oldPlaneX = e->planex;
		e->planex = e->planex * cos(rotSpeed) - e->planey * sin(rotSpeed);
		e->planey = oldPlaneX * sin(rotSpeed) + e->planey * cos(rotSpeed);
	}
	printf("%f\n", e->player_dirx);
	printf("%f\n", e->player_diry);
	return (0);
}
