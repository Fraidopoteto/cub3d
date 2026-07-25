/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 08:53:15 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:10:45 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <math.h>
# include "image.h"

typedef struct s_game t_game;

void	find_spawn_point(t_game *game);
void	move_player(t_game *game);
void	draw_player(t_game *game);

#endif
