/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoncalv <jgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:47:27 by jgoncalv          #+#    #+#             */
/*   Updated: 2017/10/26 19:24:33 by jgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sysexits.h>
#include <stdlib.h>

void	error_message(void)
{
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}
