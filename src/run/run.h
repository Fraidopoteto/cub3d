/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:54:15 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/13 09:06:52 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "init.h"
# include "window.h"
# include "error.h"
# include "parser.h"
# include "image.h"
# include "player.h"
# include "raycast.h"

void	run(t_game *game);
int		game_update(t_game *game);

#endif