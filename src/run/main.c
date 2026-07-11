/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:19:30 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/11 07:07:32 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;
	t_img	img;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&img, sizeof(t_img));
	if (argc != 2)
		return (error_int("Error\nwrong number of arguments!\n"));
	if (parser(argv[1], &map))
		return (1);
	game.map = &map;
	game.img = &img;
	init(&game);
	draw_minimap(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img->img_ptr, 0, 0);
	run(&game);
	return (0);
}