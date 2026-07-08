/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:52:41 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/08 06:00:11 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
}	t_game;

void	init(t_game *game);

#endif