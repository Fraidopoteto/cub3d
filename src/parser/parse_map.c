/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 07:55:15 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/10 11:29:55 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	_skip_metadata(char *line)
{
	int	i;

	i = 0;
	while ((line[i] == ' ' || line[i] == '\t') && line[i])
		i++;
	if (line[i] != '1')
		return(0);
	return (1);
}

static int	_fill_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (_skip_metadata(line))
		{
			map->map[i] = ft_substr(line, 0, ft_strlen(line));
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

static int _allocate_map(int fd, t_map *map)
{
	char	*line;
	int		line_count;

	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (_skip_metadata(line))
			line_count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->map = ft_calloc(line_count + 1, sizeof(char *));
	if (!map->map)
		return (1);
	map->map[line_count] = NULL;
	return (0);
}

int	read_map(t_map *map, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(error_int("Error\ncould not open file\n"));
	if (_allocate_map(fd, map))
	{
		close(fd);
		return (1);
	}
	free(get_next_line(-1));
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(error_int("Error\ncould not open file\n"));
	if (_fill_map(fd, map))
	{
		close(fd);
		return (1);
	}
	free(get_next_line(-1));
	close(fd);
	return (0);
}
