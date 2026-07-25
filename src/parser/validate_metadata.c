/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_metadata.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:28:44 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:09:31 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	_check_rgb_range(int *rgb)
{
	int	i;

	if (!rgb)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

static int	_check_paths(t_map *map)
{
	if (!map->path_no || !map->path_so)
		return (0);
	if (!map->path_we || !map->path_ea)
		return (0);
	return (1);
}

int	validate_metadata(t_map *map)
{
	if (!map)
		return (error_int("Error\nMap struct pointer is NULL\n"));
	if (!_check_paths(map))
		return (error_int("Error\nMissing texture paths\n"));
	if (!map->floor_rgb || !map->ceiling_rgb)
		return (error_int("Error\nMissing RGB color configuration\n"));
	if (!_check_rgb_range(map->floor_rgb))
		return (error_int("Error\nFloor RGB value out of range (0-255)\n"));
	if (!_check_rgb_range(map->ceiling_rgb))
		return (error_int("Error\nCeiling RGB value out of range (0-255)\n"));
	return (0);
}
