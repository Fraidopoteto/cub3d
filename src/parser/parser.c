/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 08:55:26 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/24 16:14:37 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

void	gnl_full_cleanup(void)
{
	char *line;
	while ((line = get_next_line(-1)) != NULL)
		free(line);
}

static void _free_map_resources(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	if (map->path_no)
		free(map->path_no);
	if (map->path_so)
		free(map->path_so);
	if (map->path_we)
		free(map->path_we);
	if (map->path_ea)
		free(map->path_ea);
	if (map->floor_rgb)
		free(map->floor_rgb);
	if (map->ceiling_rgb)
		free(map->ceiling_rgb);
}

int	parser(char *file_name, t_map *map)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(error_int("Error\ncould not open file\n"));
	if (read_metadata(map, fd))
	{
		_free_map_resources(map);
		gnl_full_cleanup();
		close(fd);
		return (1);
	}
	if (read_map(map, file_name))
	{
		_free_map_resources(map);
		gnl_full_cleanup();
		return (1);
	}
	close(fd);
	printf("====MAP DEBUG====\n\n");
	int y = 0;
	while (map->map[y])
	{
		printf("%i. %s", y, map->map[y]);
		y++;
	}
	if (validate_map(map))
	{
		_free_map_resources(map);
		gnl_full_cleanup();
		return (1);
	}
	if (validate_metadata(map))
	{
		_free_map_resources(map);
		gnl_full_cleanup();
		return (1);
	}
	return (0);
}
