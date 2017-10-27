/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:16 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/27 15:29:59 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static char	**get_map(const char *file, int len)
{
	char	**map;
	char	*line;
	int		i;
	int		fd;

	map = ft_tabnew(len);
	if ((fd = open(file, O_RDONLY)) == -1)
		error_message();
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	if (close(fd) == -1)
		error_message();
	return (map);
}

static char	**open_map(const char *file)
{
	char	*line;
	int		len;
	int		fd;

	len = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		error_message();
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		len++;
	}
	if (close(fd) == -1)
		error_message();
	return (get_map(file, len));
}

static int	check_extension(char *name, char *extension)
{
	int i;
	int j;

	i = ft_strlen(name);
	j = ft_strlen(extension);
	if (i == 0 || j == 0)
		return (0);
	i--;
	j--;
	while (i >= 0 && j >= 0)
	{
		if (name[i] != extension[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int			main(int ac, char **av)
{
	char	**map;
	t_env	e;

	if (ac != 2 || check_extension(av[1], ".map") == 0)
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
	mlx_hook(e.win, 17, 18, ft_quit, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
