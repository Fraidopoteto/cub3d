/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 05:15:19 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:29:07 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

int	game_update(t_game *game)
{
	move_player(game);
	ft_bzero(game->img->addr,
		WIN_WIDTH * WIN_HEIGHT * (game->img->bits_per_pixel / 8));
	raycast(game);
	draw_minimap(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
	return (0);
}

void	run(t_game *game)
{
	mlx_hook(game->win, 17, 0, (int (*)())(void *)close_game, game);
	mlx_hook(game->win, 2, 1L << 0, (int (*)())(void *)handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, (int (*)())(void *)handle_keyrelease, game);
	mlx_loop_hook(game->mlx, (int (*)())(void *)game_update, game);
	mlx_loop(game->mlx);
}
