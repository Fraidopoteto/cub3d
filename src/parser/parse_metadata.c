/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 08:14:56 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/27 14:18:52 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	if (line[0] == '\n' || line[0] == '\0' || line[0] == '1' || line[0] == '\t'  || line[0] == ' ')
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 && !map->path_no)
		return ((map->path_no = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(line, "SO ", 3) == 0 && !map->path_so)
		return ((map->path_so = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(line, "WE ", 3) == 0 && !map->path_we)
		return ((map->path_we = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(line, "EA ", 3) == 0 && !map->path_ea)
		return ((map->path_ea = get_texture_path(line, 3)) != NULL);
	if (ft_strncmp(line, "F ", 2) == 0 && !map->floor_rgb)
		return ((map->floor_rgb = get_rgb(line, 2)) != NULL);
	if (ft_strncmp(line, "C ", 2) == 0 && !map->ceiling_rgb)
		return ((map->ceiling_rgb = get_rgb(line, 2)) != NULL);
	return (-1);
}

static int	_read_line(char *line, t_map *map)
{
	int	status;

	status = _parse_line(line, map);
	free(line);
	if (status == -1)
		return (error_int("Error\nInvalid metadata\n"));
	return (0);
}

int	read_metadata(t_map *map, int fd)
{
	char	*line;
	char	*cut_line;

	line = get_next_line(fd);
	while (line)
	{
		cut_line = _cut_newline(line);
		free(line);
		if (_read_line(cut_line, map))
		{
			line = get_next_line(fd);
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			return (1);
		}
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
