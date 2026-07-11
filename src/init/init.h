/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:52:41 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/11 06:33:54 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# include "parser.h"
# include "image.h"

typedef struct s_img t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*img;
}	t_game;

void	init(t_game *game);

#endif