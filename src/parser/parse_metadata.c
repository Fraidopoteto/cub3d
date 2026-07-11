/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 08:14:56 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/10 16:00:20 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

static char	*_cut_newline(char *line)
{
	char	*cut_line;
	int		len;

	len = 0;
	while (line[len] != '\n' && line[len])
		len++;
	cut_line = ft_substr(line, 0, len);
	return (cut_line);
}

static int	_parse_line(char *line, t_map *map)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (0);
	if (ft_strncmp(&line[0], "NO ", 3) == 0)
		return ((map->path_no = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(&line[0], "SO ", 3) == 0)
		return ((map->path_so = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(&line[0], "WE ", 3) == 0)
		return ((map->path_we = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(&line[0], "EA ", 3) == 0)
		return ((map->path_ea = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(&line[0], "F ", 2) == 0)
		return ((map->floor_rgb = get_rgb(line, 2)) != NULL);
	if (ft_strncmp(&line[0], "C ", 2) == 0)
		return ((map->ceiling_rgb = get_rgb(line, 2)) != NULL);
	return (-1);
}

static int	_read_line(char *line, t_map *map, int *element_count)
{
	int	status;

	status = _parse_line(line, map);
	if (status == -1)
		return (error_int("Error\nInvalid metadata or wrong order\n"));
	if (status == 1)
		(*element_count)++;
	free(line);
	return (0);
}

int	read_metadata(t_map *map, int fd)
{
	int		element_count;
	char	*line;
	char	*cut_line;

	element_count = 0;
	line = get_next_line(fd);
	while (line && element_count != 6)
	{
		cut_line = _cut_newline(line);
		if (_read_line(cut_line, map, &element_count))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	free(get_next_line(-1));
	close(fd);
	return (0);
}
