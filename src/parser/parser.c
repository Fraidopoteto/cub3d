/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 08:55:26 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/10 15:30:05 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser(char *file_name, t_map *map)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(error_int("Error\ncould not open file\n"));
	if (read_metadata(map, fd))
		return (1);
	printf("===METADATA DEBUG===\n\n");
	printf("--TEXTURE PATHS\n");
	printf("NO PATH: %s\n", map->path_no);
	printf("SO PATH: %s\n", map->path_so);
	printf("EA PATH: %s\n", map->path_ea);
	printf("WE PATH: %s\n", map->path_we);
	printf("\n--RGB CODES\n");
	printf("F: %i,%i,%i\n", map->floor_rgb[0], map->floor_rgb[1], map->floor_rgb[2]);
	printf("C: %i,%i,%i\n\n", map->ceiling_rgb[0], map->ceiling_rgb[1], map->ceiling_rgb[2]);
	if (read_map(map, file_name))
		return (1);
	printf("====MAP DEBUG====\n\n");
	int y = 0;
	while (map->map[y])
	{
		printf("%i. %s", y, map->map[y]);
		y++;
	}
	printf("\n");
	close(fd);
	if (validate_map(map))
		return (1);
	if (validate_metadata(map))
		return (1);
	return (0);
}