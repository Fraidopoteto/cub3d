/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:19:30 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:11:19 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static int _check_extension(char *str)
{
	int	size;

	size = ft_strlen(str);
	if (size < 5)
		return (1);
	if (ft_strncmp(&str[size - 4], ".cub", 4))
		return (1);
	return (0);
}


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
	if (_check_extension(argv[1]))
		return (error_int("Error\nwrong file extension\n"));
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
