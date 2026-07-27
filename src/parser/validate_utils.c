/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 14:03:14 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/27 14:15:53 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int validate_texture(t_map *map)
{
	int	fd;

	fd = open(map->path_no, O_RDONLY);
	if (fd == -1)
		return (error_int("Error\ncould not find texture\n"));
	close(fd);
	fd = open(map->path_so, O_RDONLY);
	if (fd == -1)
		return (error_int("Error\ncould not find texture\n"));
	close(fd);
	fd = open(map->path_ea, O_RDONLY);
	if (fd == -1)
		return (error_int("Error\ncould not find texture\n"));
	close(fd);
	fd = open(map->path_we, O_RDONLY);
	if (fd == -1)
		return (error_int("Error\ncould not find texture\n"));
	close(fd);
	return (0);
}
