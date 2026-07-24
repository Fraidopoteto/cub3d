/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:52:41 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/13 09:23:16 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# include "parser.h"
# include "image.h"
# include "player.h"

typedef struct s_player
{
	double	pos_x;     // Exakte Position in der Map (z.B. 3.5)
	double	pos_y;
	double	dir_x;     // Blickrichtung Vektor
	double	dir_y;
	double	move_speed;
	double	rot_speed;
	double plane_x; // NEU: X-Vektor der Kamera-Ebene
    double plane_y; // NEU: Y-Vektor der Kamera-Ebene
}	t_player;

typedef struct s_img
{
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;  // NEU: Wichtig für Texturen
    int     height; // NEU: Wichtig für Texturen
} t_img;

typedef struct s_game
{
	t_player	player;
	void		*mlx;
	void		*win;
	t_map		*map;
	t_img		*img;
	int			keys[6];
	t_img		texture[4];
}	t_game;

void	init(t_game *game);

#endif