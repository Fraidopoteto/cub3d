/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 08:54:42 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:10:35 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "init.h"

static void	_set_player_dir(t_player *p, char dir)
{
	p->dir_x = 0.0;
	p->dir_y = 0.0;
	p->plane_x = 0.0;
	p->plane_y = 0.0;
	if (dir == 'N')
		p->dir_y = -1.0;
	else if (dir == 'S')
		p->dir_y = 1.0;
	else if (dir == 'E')
		p->dir_x = 1.0;
	else if (dir == 'W')
		p->dir_x = -1.0;
	if (dir == 'N' || dir == 'S')
		p->plane_x = -p->dir_y;
	else
		p->plane_y = p->dir_x;
}

void	find_spawn_point(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (ft_strchr("NSWE", game->map->map[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				_set_player_dir(&game->player, game->map->map[y][x]);
				game->map->map[y][x] = '0';
				return ;
			}
		}
	}
}

void	draw_player(t_game *game)
{
	int	t_x;
	int	t_y;
	int	x;
	int	y;

	t_x = (int)game->player.pos_x;
	t_y = (int)game->player.pos_y;
	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
		{
			if (x == 0 || y == 0 || x == TILE_SIZE - 1 || y == TILE_SIZE - 1)
				put_pixel_to_img(game->img, (t_x * TILE_SIZE) + x,
					(t_y * TILE_SIZE) + y, 0x00000000);
			else
				put_pixel_to_img(game->img, (t_x * TILE_SIZE) + x,
					(t_y * TILE_SIZE) + y, 0x0000FF00);
		}
	}
}
