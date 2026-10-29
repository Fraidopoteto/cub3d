/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:00:23 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:43:42 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	_flood_fill(char **map, int y, int x)
{
	if (y < 0 || !map[y] || x < 0 || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '\n')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	map[y][x] = 'X';
	if (!_flood_fill(map, y + 1, x) || !_flood_fill(map, y - 1, x)
		|| !_flood_fill(map, y, x + 1) || !_flood_fill(map, y, x - 1))
		return (0);
	return (1);
}

static int	_process_char(char c, int vec[2], int *p_y, int *p_x)
{
	if (ft_strchr("NSWE", c))
	{
		*p_y = vec[0];
		*p_x = vec[1];
		return (1);
	}
	if (!ft_strchr("01 \t\n", c))
	{
		printf("%c", c);
		return (-1);
	}
	return (0);
}

static int	_check_chars_and_player(t_map *map, int *p_y, int *p_x)
{
	int	y;
	int	x;
	int	pc;
	int	res;

	y = -1;
	pc = 0;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			res = _process_char(map->map[y][x], (int []){y, x}, p_y, p_x);
			if (res == 1)
				pc++;
			else if (res == -1)
				return (error_int("Error\nInvalid char in map\n"));
		}
	}
	if (pc != 1)
		return (error_int("Error\nMap must have exactly one player\n"));
	return (0);
}

int	validate_map(t_map *map)
{
	char	**temp_map;
	int		player_y;
	int		player_x;

	player_y = 0;
	player_x = 0;
	if (!map || !map->map || !map->map[0])
		return (error_int("Error\nMap is empty\n"));
	if (_check_chars_and_player(map, &player_y, &player_x))
		return (1);
	temp_map = _copy_map(map->map);
	if (!temp_map)
		return (error_int("Error\nMalloc failed in validator\n"));
	if (!_flood_fill(temp_map, player_y, player_x))
	{
		_free_matrix(temp_map);
		return (error_int("Error\nMap is not enclosed by walls\n"));
	}
	_free_matrix(temp_map);
	return (0);
}
