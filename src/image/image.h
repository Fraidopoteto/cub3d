/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 06:13:05 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:50:08 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TILE_SIZE 10

# include "libft.h"
# include "parser.h"
# include "init.h"

typedef struct s_game	t_game;
typedef struct s_img	t_img;

void	draw_minimap(t_game *game);
void	put_pixel_to_img(t_img *img, int x, int y, int color);

#endif
