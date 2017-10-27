/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <nbuhler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:10:02 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/26 19:21:55 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_move(int keycode, t_env *e)
{
	if (keycode == 53)
	{
		mlx_destroy_image(e->mlx, e->img);
		mlx_clear_window(e->mlx, e->win);
		exit(0);
	}
	if (keycode == UP_ARROW)
		e->player_move_up = !e->player_move_up;
	if (keycode == DOWN_ARROW)
		e->player_move_down = !e->player_move_down;
	if (keycode == RIGHT_ARROW)
		e->player_move_right = !e->player_move_right;
	if (keycode == LEFT_ARROW)
		e->player_move_left = !e->player_move_left;
	return (0);
}

int		key_press(int k, t_env *e)
{
	key_move(k, e);
	return (0);
}
