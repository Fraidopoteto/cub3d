/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:51:28 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 12:27:23 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

static void	_free_map_resources(t_map *map)
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

void	cleanup(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = -1;
	while (++i < 4)
	{
		if (game->texture[i].img_ptr)
			mlx_destroy_image(game->mlx, game->texture[i].img_ptr);
	}
	if (game->img && game->img->img_ptr)
		mlx_destroy_image(game->mlx, game->img->img_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		_free_map_resources(game->map);
}

int	close_game(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}
