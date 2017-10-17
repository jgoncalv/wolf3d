/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:52 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/17 16:53:04 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h>

# define WIN_H 600
# define WIN_W 600
# define PROG_NAME "Wolf3D"

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

typedef struct	s_map
{
	int			mapX;
	int			mapY;
	int			**map;
	int			map_l;
	int			map_w;
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

int	parser(char **map);
void	error_message();
t_env init(char **map);


#endif
