/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:37:13 by jgoncalv          #+#    #+#             */
/*   Updated: 2016/12/12 12:32:58 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabnew(size_t n)
{
	char		**tab;
	size_t		i;

	i = 0;
	if (!(tab = (char**)ft_memalloc(sizeof(char**) * (n + 1))))
		return (NULL);
	tab[n] = NULL;
	return (tab);
}
