/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:46:12 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/27 15:12:03 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	get_color(t_env *e, t_ray *ray)
{
	if (ray->side == 1)
	{
		if ((ray->stepx == -1 && ray->stepy == -1) ||
			(ray->stepx == 1 && ray->stepy == -1))
			return (e->color_east);
		if ((ray->stepx == -1 && ray->stepy == 1) ||
			(ray->stepx == 1 && ray->stepy == 1))
			return (e->color_west);
	}
	if ((ray->stepx == -1 && ray->stepy == -1) ||
		(ray->stepx == -1 && ray->stepy == 1))
		return (e->color_north);
	return (e->color_south);
}

static int	smog(double d, int color)
{
	int	r;
	int	g;
	int	b;

	r = color / 256 / 256;
	g = color / 256 % 256;
	b = color % 256;
	if (r > 0)
		r = r - ((r * d) / SMOG_DIST);
	if (g > 0)
		g = g - ((g * d) / SMOG_DIST);
	if (b > 0)
		b = b - ((b * d) / SMOG_DIST);
	r = r <= 0 || r > 255 ? 0 : r;
	g = g <= 0 || g > 255 ? 0 : g;
	b = b <= 0 || b > 255 ? 0 : b;
	color = (r * 256 * 256) + (g * 256) + b;
	return (color);
}

void		draw_line(t_env *e, t_ray *ray, int x)
{
	int		i;
	double	init;
	double	d;

	i = -1;
	init = (WIN_H - 1) / (SQUARE_MAP_SIZE - 1);
	while (++i < ray->draw_start)
	{
		d = (double)i / init;
		d = d < 0 ? d * -1 : d;
		put_pxl(e, x, i, smog(d, e->colorsky));
	}
	i--;
	while (++i <= ray->draw_end && i < WIN_H)
		put_pxl(e, x, i, smog(ray->walldist, get_color(e, ray)));
	i--;
	while (++i < WIN_H)
	{
		d = (SQUARE_MAP_SIZE - 1) - (double)i / init;
		d = d < 0 ? d * -1 : d;
		put_pxl(e, x, i, smog(d, e->colorground));
	}
}
