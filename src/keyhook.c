/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 18:58:40 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/17 19:24:00 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


int			keyhook(int keycode, t_env *e)
{
	int moveSpeed = 1;
	int rotSpeed = 1;

	if (keycode == 53)
	{
		mlx_destroy_image(e->mlx, e->img);
		mlx_clear_window(e->mlx, e->win);
		exit(0);
	}
	if (keycode == UP_ARROW)
	{
		if(e->map.map[(int)(e->player.posX + e->player.dirX * moveSpeed)][(int)(e->player.posY)] == 0)
			e->player.posX += e->player.dirX * moveSpeed;
		if(e->map.map[(int)(e->player.posX)][(int)(e->player.posY + e->player.dirY * moveSpeed)] == 0)
			e->player.posY += e->player.dirY * moveSpeed;
	}
	else if (keycode == DOWN_ARROW)
	{
		if(e->map.map[(int)(e->player.posX - e->player.dirX * moveSpeed)][(int)(e->player.posY)] == 0)
			e->player.posX -= e->player.dirX * moveSpeed;
		if(e->map.map[(int)(e->player.posX)][(int)(e->player.posY - e->player.dirY * moveSpeed)] == 0)
			e->player.posY -= e->player.dirY * moveSpeed;
	}
	else if (keycode == RIGHT_ARROW)
	{
		double oldDirX = e->player.dirX;
		e->player.dirX = e->player.dirX * cos(-rotSpeed) - e->player.dirY * sin(-rotSpeed);
		e->player.dirY = oldDirX * sin(-rotSpeed) + e->player.dirY * cos(-rotSpeed);
		double oldPlaneX = e->player.planeX;
		e->player.planeX = e->player.planeX * cos(-rotSpeed) - e->player.planeY * sin(-rotSpeed);
		e->player.planeY = oldPlaneX * sin(-rotSpeed) + e->player.planeY * cos(-rotSpeed);
	}
	else if (keycode == LEFT_ARROW)
	{
		double oldDirX = e->player.dirX;
		e->player.dirX = e->player.dirX * cos(rotSpeed) - e->player.dirY * sin(rotSpeed);
		e->player.dirY = oldDirX * sin(rotSpeed) + e->player.dirY * cos(rotSpeed);
		double oldPlaneX = e->player.planeX;
		e->player.planeX = e->player.planeX * cos(rotSpeed) - e->player.planeY * sin(rotSpeed);
		e->player.planeY = oldPlaneX * sin(rotSpeed) + e->player.planeY * cos(rotSpeed);
	}
	return (0);
}
