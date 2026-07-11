/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 06:13:05 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/11 06:33:37 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TILE_SIZE 10

# include "libft.h"
# include "init.h"
# include "parser.h"

typedef struct s_game t_game;

typedef struct s_img
{
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_img;

void	draw_minimap(t_game *game);

#endif