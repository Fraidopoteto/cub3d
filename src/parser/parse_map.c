/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 07:55:15 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 12:30:53 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	_skip_metadata(char *line)
{
	if (ft_strncmp(&line[0], "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[0], "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[0], "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[0], "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[0], "F ", 2) == 0)
		return (1);
	if (ft_strncmp(&line[0], "C ", 2) == 0)
		return (1);
	if (line[0] == '\n')
		return (1);
	return (0);
}
static void	gnl_cleanup(int fd)
{
	char *line;
	while ((line = get_next_line(fd)) != NULL)
		free(line);
}

static int	_fill_map(int fd, t_map *map)
{
	char		*line;
	int			i;
	t_skip_meta	meta;

	ft_memset(&meta, 0, sizeof(t_skip_meta));
	i = 0;
	line = get_next_line(fd);
	while (line && _skip_metadata(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line[0] != '\n')
	{
		map->map[i] = ft_substr(line, 0, ft_strlen(line));
		if (ft_strlen(map->map[i]) > 100)
			return (free(line), error_int("Error\nMap too big\n"));
		i++;
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
	while (line && _skip_metadata(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line[0] != '\n')
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (line_count > 100)
		return(error_int("Error\nMap too big\n"));
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
		gnl_cleanup(fd);
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
		gnl_cleanup(fd);
		close(fd);
		return (1);
	}
	gnl_cleanup(fd);
	close(fd);
	return (0);
}
