/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 05:46:47 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/12 08:51:57 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	if (keycode == 119) // W
		game->keys[0] = 1;
	if (keycode == 115) // S
		game->keys[1] = 1;
	if (keycode == 97)  // A
		game->keys[2] = 1;
	if (keycode == 100) // D
		game->keys[3] = 1;
	// Pfeiltasten für Rotation (Links/Rechts)
	if (keycode == 65361) // Left
		game->keys[4] = 1;
	if (keycode == 65363) // Right
		game->keys[5] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == 119) // W
		game->keys[0] = 0;
	if (keycode == 115) // S
		game->keys[1] = 0;
	if (keycode == 97)  // A
		game->keys[2] = 0;
	if (keycode == 100) // D
		game->keys[3] = 0;
	if (keycode == 65361) // Left
		game->keys[4] = 0;
	if (keycode == 65363) // Right
		game->keys[5] = 0;
	return (0);
}