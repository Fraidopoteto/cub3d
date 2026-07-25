/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:21:43 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 12:21:56 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	_move_step(t_game *g, double step_x, double step_y)
{
	double	nx;
	double	ny;
	double	off_x;
	double	off_y;

	nx = g->player.pos_x + step_x;
	ny = g->player.pos_y + step_y;
	off_x = 0.15;
	if (step_x < 0)
		off_x = -0.15;
	off_y = 0.15;
	if (step_y < 0)
		off_y = -0.15;
	if (g->map->map[(int)g->player.pos_y][(int)(nx + off_x)] != '1')
		g->player.pos_x = nx;
	if (g->map->map[(int)(ny + off_y)][(int)g->player.pos_x] != '1')
		g->player.pos_y = ny;
}

static void	_rotate_player(t_game *g, double rs)
{
	double	old_dir;
	double	old_plane;

	old_dir = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos(rs) - g->player.dir_y * sin(rs);
	g->player.dir_y = old_dir * sin(rs) + g->player.dir_y * cos(rs);
	old_plane = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos(rs) - g->player.plane_y * sin(rs);
	g->player.plane_y = old_plane * sin(rs) + g->player.plane_y * cos(rs);
}

void	move_player(t_game *game)
{
	double	s;

	s = game->player.move_speed;
	if (game->keys[0])
		_move_step(game, game->player.dir_x * s, game->player.dir_y * s);
	if (game->keys[1])
		_move_step(game, -game->player.dir_x * s, -game->player.dir_y * s);
	if (game->keys[2])
		_move_step(game, game->player.dir_y * s, -game->player.dir_x * s);
	if (game->keys[3])
		_move_step(game, -game->player.dir_y * s, game->player.dir_x * s);
	if (game->keys[4])
		_rotate_player(game, -game->player.rot_speed);
	if (game->keys[5])
		_rotate_player(game, game->player.rot_speed);
}