/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 07:51:32 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/10 11:36:28 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "get_next_line.h"
#include "libft.h"
#include "error.h"

typedef struct s_map
{
	char **map;
	char *path_no;
	char *path_so;
	char *path_we;
	char *path_ea;
	int	*floor_rgb;
	int *ceiling_rgb;
} t_map;

char	**cpy_map(int max_y, int max_x, char **map);
char	*get_texture_path(char *line, int i);
int		*get_rgb(char *line, int i);
int		read_metadata(t_map *map, int fd);
int		read_map(t_map *map, char *file_name);
int		parser(char *file_name, t_map *map);

#endif