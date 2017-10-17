/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuhler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 11:39:28 by nbuhler           #+#    #+#             */
/*   Updated: 2017/10/17 11:40:47 by nbuhler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/includes/libft.h"

# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6

typedef struct	s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;

}				t_player;

typedef struct 	s_ray
{
	double ray_posX;
	double ray_posY;
	double cameraX;
	double ray_dirX;
	double ray_dirY;
	double side_distX;
	double side_distY;
	double delta_distX;
	double delta_distY;
	double perp_wallDist;
	int		stepX;
	int 	stepY;
	int		hit;
	int 	side;
	int 	lineHeight;
	int 	drawStart;
	int 	drawEnd;

}				t_ray;

typedef struct s_map
{
	int mapX;
	int mapY;
	int	**map;
}				t_map;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pxl;
	int			width;
	int			height;
	int			bpp;
	int			s_line;
	int			ed;
	int			colorsky;
	int			color;
	int 		color2;
	struct s_player player;
	struct s_map map;
	struct s_ray ray;
}				t_env;



#endif