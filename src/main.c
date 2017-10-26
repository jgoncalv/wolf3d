/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:16 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/26 19:03:51 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static char	**open_map(const char *file)
{
	char	**map;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		i++;
	close(fd);
	map = ft_tabnew(i);
	fd = open(file, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map[i] = ft_strdup(line);
		i++;
	}
	close(fd);
	return (map);
}

int			main(int ac, char **av)
{
	char	**map;
	t_env	e;

	if (ac != 2)
		return (0);
	map = open_map(av[1]);
	if (map == NULL || parser(map) == 0)
	{
		ft_tabdel(map, ft_tablen(map));
		return (0);
	}
	e = init(map);
	ft_tabdel(map, ft_tablen(map));
	mlx_do_key_autorepeatoff(e.mlx);
	mlx_key_hook(e.win, key_press, &e);
	mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, key_press, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
