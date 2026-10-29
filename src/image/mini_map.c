/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 06:15:29 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:50:41 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static void	_draw_tile(t_img *img, int start_x, int start_y, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			if (x == 0 || y == 0 || x == TILE_SIZE - 1 || y == TILE_SIZE - 1)
				put_pixel_to_img(img, start_x + x, start_y + y, 0x00000000);
			else
				put_pixel_to_img(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

static int	_get_tile_color(char c)
{
	if (c == '1')
		return (0x00FFFFFF);
	if (c == '0')
		return (0x00555555);
	if (ft_strchr("NSWE", c))
		return (0x00555555);
	return (-1);
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	color;

	if (!game || !game->map || !game->map->map || !game->img
		|| !game->img->addr)
		return ;
	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			color = _get_tile_color(game->map->map[y][x]);
			if (color != -1)
				_draw_tile(game->img, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
}
