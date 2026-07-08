/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 07:52:03 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/08 08:04:29 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**_allocate_map_copy(int max_y, int max_x)
{
	char	**map_cpy;
	int		y;

	y = 0;
	map_cpy = malloc(sizeof(char *) * max_y);
	if (!map_cpy)
		return (NULL);
	while (y < max_y)
	{
		map_cpy[y] = malloc(sizeof(char) * (max_x + 1));
		if (!map_cpy[y])
		{
			while (y > 0)
			{
				y--;
				free(map_cpy[y]);
			}
			free(map_cpy);
			return (NULL);
		}
		y++;
	}
	return (map_cpy);
}

char	**cpy_map(int max_y, int max_x, char **map)
{
	char	**map_cpy;
	int		y;
	int		x;

	map_cpy = _allocate_map_copy(max_y, max_x);
	if (!map_cpy)
		return (NULL);
	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			map_cpy[y][x] = map[y][x];
			x++;
		}
		map_cpy[y][x] = '\0';
		y++;
	}
	return (map_cpy);
}
