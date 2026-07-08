/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:51:28 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/08 05:42:18 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

int	close_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	cleanup();
	exit(0);
	return (0);
}	

void	cleanup(void)
{
	printf("cleanup...");
}