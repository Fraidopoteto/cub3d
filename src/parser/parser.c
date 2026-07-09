/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 08:55:26 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/09 14:36:19 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(char *file_name)
{
	t_map map;

	read_metadata(file_name, &map);
	printf("===PARSER DEBUGG===\n\n");
	printf("===TEXTURE PATHS===\n");
	printf("NO PATH: %s\n", map.path_no);
	printf("SO PATH: %s\n", map.path_so);
	printf("EA PATH: %s\n", map.path_ea);
	printf("WE PATH: %s\n", map.path_we);
	printf("\n=====RGB CODES=====\n");
	printf("F: %i,%i,%i\n", map.floor[0], map.floor[1], map.floor[2]);
	printf("C: %i,%i,%i\n", map.ceiling[0], map.ceiling[1], map.ceiling[2]);
}