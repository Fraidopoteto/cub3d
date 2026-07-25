/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 05:09:12 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:12:22 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	create_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	if (!game->win)
		return;
}
