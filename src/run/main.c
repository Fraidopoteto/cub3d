/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:19:30 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/08 11:18:00 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return(error_int("Error\nwrong number of arguments!"));
	parser(argv[1]);
	init(&game);
	create_window(&game);
	run(&game);
}