/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:37:01 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/24 18:37:10 by nbuhler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WOLF_H
# define	WOLF_H

typedef struct s_ray
{
	double	posx;
	double	posy;
	
	double	dirx;
	double	diry;
	
	double	sidedx;
	double	sidedy;
	
	double	ddistx;
	double	ddisty;
	
	double	walldist;

	int		side;

	int		stepx;
	int		stepy;

	double	camerax;

	int 	**map;
	int		mapx;
	int		mapy;
	double 	draw_start;
	double 	draw_end;

}				t_ray;			

#endif
