/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 05:15:19 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/13 09:05:51 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

int game_update(t_game *game)
{
    // 1. Player bewegen
    move_player(game);
    
    // 2. Kompletten Hintergrund schwarz leeren
    ft_bzero(game->img->addr, WIN_WIDTH * WIN_HEIGHT * (game->img->bits_per_pixel / 8));
    
    // 3. 3D-Welt raycasten! (Die neue Funktion)
    raycast(game);
    
    // 4. (Optional) Minimap als HUD oben drüber zeichnen
    // Wenn die Minimap stört, kommentiere diese beiden Zeilen einfach aus
    draw_minimap(game);
    draw_player(game);
    
    // 5. Bild ans Fenster pushen
    mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
    return (0);
}

void	run(t_game *game)
{
	// Hooks registrieren
	mlx_hook(game->win, 17, 0, (int (*)())(void *)close_game, game);
	mlx_hook(game->win, 2, 1L << 0, (int (*)())(void *)handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, (int (*)())(void *)handle_keyrelease, game); // NEU
	
	// Loop starten
	mlx_loop_hook(game->mlx, (int (*)())(void *)game_update, game);
	mlx_loop(game->mlx);
}
