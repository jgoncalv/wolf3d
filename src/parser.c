/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 17:18:48 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/26 19:02:51 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	check_line_width(char **map, int width)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) != (size_t)width)
			return (0);
		i++;
	}
	return (1);
}

static int	check_wall_arround(char **map, int width, int length)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] < '1' || map[i][0] > '9' || map[i][width - 1] < '1'
		|| map[i][width - 1] > '9')
			return (0);
		i++;
	}
	i = 0;
	while (map[0][i] && map[length - 1][i])
	{
		if (map[0][i] < '1' || map[0][i] > '9' || map[length - 1][i] < '1'
		|| map[length - 1][i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_space_for_player(char **map)
{
	int i;
	int j;
	int count_space;

	i = 0;
	count_space = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] < '0' || map[i][j] > '9')
				return (0);
			if (map[i][j] == '0')
				count_space++;
			j++;
		}
		i++;
	}
	if (count_space == 0)
		return (0);
	return (1);
}

int			parser(char **map)
{
	int width;
	int length;

	if (!map || !*map)
		return (0);
	width = ft_strlen(*map);
	length = ft_tablen(map);
	if (width != SQUARE_MAP_SIZE || width != length)
		return (0);
	if (check_line_width(map, width) == 0)
		return (0);
	if (check_wall_arround(map, width, length) == 0)
		return (0);
	if (check_space_for_player(map) == 0)
		return (0);
	return (1);
}
