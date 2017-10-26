/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:52 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/26 18:14:12 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h>

# define WIN_W 800
# define WIN_H 600
# define PROG_NAME "Wolf3D"
# define SQUARE_MAP_SIZE 10
# define MINI_MAPW 160
# define MINI_MAPH 160
# define SMOG_DIST 4

# define KEY_PRESS_MASK (1L<<0)
# define KEY_PRESS 2

# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

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

	int			player_move_up;
	int			player_move_down;
	int			player_move_right;
	int			player_move_left;
	double		player_posx;
	double		player_posy;
	double		player_dirx;
	double		player_diry;
	double		planex;
	double		planey;

	int			mapx;
	int			mapy;
	int			map[SQUARE_MAP_SIZE][SQUARE_MAP_SIZE];

	int			colorsky;
	int			colorground;
	int 		color_east;
	int 		color_west;
	int 		color_north;
	int 		color_south;
}				t_env;

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

	int		mapx;
	int		mapy;
	double 	draw_start;
	double 	draw_end;

}				t_ray;


typedef struct		s_draw
{
	int				color;
	int				zi;
	int				zf;
	int				xi;
	int				yi;
	int				xf;
	int				yf;
	int				dx;
	int				dy;
	int				xinc;
	int				yinc;
	int				decalx;
	int				decaly;
	int				offsetx;
	int				offsety;
}					t_draw;

int		parser(char **map);
void	error_message();
t_env	init(char **map);
void	raycasting(t_env *e);
int			keyhook(int keycode, t_env *e);
void	fill_pixel(char **img, int x, int y, int color);
void		draw_ray(t_env *e, double xf, double yf, int color);
int 		loop_hook(t_env *e);
int 		key_press(int k, t_env *e);

#endif
