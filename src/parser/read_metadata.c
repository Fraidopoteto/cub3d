/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 08:14:56 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/08 11:35:39 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void _free_split(char**split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	*_get_rgb(char *line, int i)
{
	char	**split;
	int		*rgb;
	int		count;

	count = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	split = ft_split(line, ',');
	if (!split)
		return (NULL);
	while (split[count])
		count++;
	if (count != 3)
		return (error_NULL("Error\nwrong number of RGB elements\n"));
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		_free_split(split);
		return (NULL);
	}
	count = 0;
	while (count++ != 3)
		rgb[count] = ft_atoi(split[count]);
	return (rgb);
}

static char *_get_texture_path(char *line, int i)
{
    int     start;
    int     len;
    char    *path;

    while(line[i] == '\t' || line[i] == ' ')
		i++;
    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
        i++;
    len = i - start;
    if (len <= 0)
        return (NULL);
    path = ft_substr(line, start, len);
    return (path);
}

static int _parse_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	else if (ft_strncmp(&line[i], "NO ", 3) == 0 && !map->path_no)
		return ((map->path_no = _get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "SO ", 3) == 0 && !map->path_so)
		return ((map->path_so = _get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "WE ", 3) == 0 && !map->path_we)
		return ((map->path_we = _get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "EA ", 3) == 0 && !map->path_ea)
		return ((map->path_ea = _get_texture_path(line, i + 3)) != NULL);
	else if (ft_strncmp(&line[i], "C ", 2) == 0 && !map->ceiling)
		return ((map->ceiling = _get_rgb(line, i + 2)) != NULL);
	else if (ft_strncmp(&line[i], "F ", 2) == 0 && !map->ceiling)
		return ((map->floor = _get_rgb(line, i + 2)) != NULL);
	return(-1);
}

int	read_metadata(char *file_name, t_map *map)
{
	int		fd;
	int		status;
	int		element_count;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(error_int("Error\ncould not open file\n"));
	element_count = 0;
	line = get_next_line(fd);
	while (line || element_count != 6)
	{
		status = _parse_line(line, map);
		if (status == -1)
		{
			free(line);
			return (error_int("Error\nInvalid element found in metadata\n"));
		}
		if (status == 1)
			element_count++;
		line = get_next_line(fd);
	}
	if (element_count != 6)
		return (error_int("Error\nwrong number of elements\n"));
	return (0);
}
