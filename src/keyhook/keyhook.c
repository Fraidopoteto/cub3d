/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 05:46:47 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 12:30:29 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	if (keycode == 119)
		game->keys[0] = 1;
	if (keycode == 115)
		game->keys[1] = 1;
	if (keycode == 97)
		game->keys[2] = 1;
	if (keycode == 100)
		game->keys[3] = 1;
	if (keycode == 65361)
		game->keys[4] = 1;
	if (keycode == 65363)
		game->keys[5] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys[0] = 0;
	if (keycode == 115)
		game->keys[1] = 0;
	if (keycode == 97)
		game->keys[2] = 0;
	if (keycode == 100)
		game->keys[3] = 0;
	if (keycode == 65361)
		game->keys[4] = 0;
	if (keycode == 65363)
		game->keys[5] = 0;
	return (0);
}
