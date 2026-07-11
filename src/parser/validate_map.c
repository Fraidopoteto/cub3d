/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:00:23 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/10 15:16:59 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static char	**_copy_map(char **map)
{
	char	**copy;
	int		len;
	int		i;

	len = 0;
	while (map[len])
		len++;
	copy = ft_calloc(len + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (_free_matrix(copy), NULL);
		i++;
	}
	copy[len] = NULL;
	return (copy);
}

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

static int	_check_chars_and_player(t_map *map, int *p_y, int *p_x)
{
	int	y;
	int	x;
	int	player_count;

	y = -1;
	player_count = 0;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_strchr("NSWE", map->map[y][x]) && map->map[y][x] != '\0')
			{
				*p_y = y;
				*p_x = x;
				player_count++;
			}
			else if (!ft_strchr("01 \t\n", map->map[y][x]))
				return (error_int("Error\nInvalid char in map\n"));
		}
	}
	if (player_count != 1)
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
