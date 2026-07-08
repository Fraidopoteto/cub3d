/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 07:55:15 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/08 08:04:44 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	_line_length(char *line)
{
	int	len;

	len = 0;
	while (line[len] != '\0' && line[len] != '\n')
		len++;
	return (len);
}

static char	**_store_lines(int fd, int *max_y, int *max_x)
{
	char	**line_storage;
	char	*line;
	int		line_len;

	line_storage = malloc(sizeof(char *) * 1000);
	if (!line_storage)
		return (NULL);
	*max_y = 0;
	*max_x = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_storage[*max_y] = line;
		(*max_y)++;
		line_len = _line_length(line);
		if (line_len > *max_x)
			*max_x = line_len;
		line = get_next_line(fd);
	}
	return (line_storage);
}

static char	**_fill_map(char **line_storage, int max_y, int max_x)
{
	char	**map;
	int		y;
	int		x;

	map = malloc(sizeof(char *) * (max_y + 1));
	if (!map)
		return (NULL);
	y = 0;
	while (y < max_y)
	{
		map[y] = malloc(sizeof(char) * (max_x + 1));
		if (!map[y])
			return (NULL);
		x = 0;
		while (line_storage[y][x] != '\0' && line_storage[y][x] != '\n')
		{
			map[y][x] = line_storage[y][x];
			x++;
		}
		map[y][x] = '\0';
		free(line_storage[y]);
		y++;
	}
	map[max_y] = NULL;
	return (map);
}

char	**read_map(int fd, int *max_y, int *max_x)
{
	char	**line_storage;
	char	**map;

	*max_y = 0;
	*max_x = 0;
	line_storage = _store_lines(fd, max_y, max_x);
	if (!line_storage)
		return (NULL);
	map = _fill_map(line_storage, *max_y, *max_x);
	free(line_storage);
	return (map);
}
