/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 07:51:32 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/08 11:34:39 by joschmun         ###   ########.fr       */
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
#include "error.h"

typedef struct s_map
{
	char *path_no;
	char *path_so;
	char *path_we;
	char *path_ea;
	int	*floor;
	int *ceiling;
} t_map;

char	**cpy_map(int max_y, int max_x, char **map);
char	**read_map(int fd, int *max_y, int *max_x);
int		read_metadata(char *file_name, t_map *map);
void	parser(char *file_name);

#endif