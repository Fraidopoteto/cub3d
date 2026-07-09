/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 08:14:56 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/09 14:32:11 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char *_cut_newline(char *line)
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
	int	i;

	i = 0;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	else if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return ((map->path_no = get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return ((map->path_so = get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return ((map->path_we = get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return ((map->path_ea = get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return ((map->ceiling = get_rgb(line, i + 2)) != NULL);
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
		return ((map->floor = get_rgb(line, i + 2)) != NULL);
	return(-1);
}

static int	_read_line(char *line, t_map *map, int *element_count)
{
	int status;

	status = _parse_line(line, map);
	if (status == -1)
		return (error_int("Error\nInvalid element found in metadata\n"));
	if (status == 1)
		(*element_count)++;
	free(line);
	return (0);
}

int	read_metadata(char *file_name, t_map *map)
{
	int		fd;
	int		element_count;
	char	*line;
	char	*cut_line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(error_int("Error\ncould not open file\n"));
	element_count = 0;
	line = get_next_line(fd);
	while (line && element_count != 6)
	{
		cut_line = _cut_newline(line);
		if (_read_line(cut_line, map, &element_count))
			break ;
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
