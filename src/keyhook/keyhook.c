/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 05:46:47 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/10 11:40:27 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyhook.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	return (0);
}