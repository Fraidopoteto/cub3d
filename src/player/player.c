/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 08:54:42 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/13 09:09:49 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "init.h"

static void _set_player_dir(t_player *player, char dir)
{
    if (dir == 'N') {
        player->dir_x = 0.0;  player->dir_y = -1.0;
        player->plane_x = 1.0; player->plane_y = 0.0; // Von 0.66 auf 1.0 erhöht
    }
    else if (dir == 'S') {
        player->dir_x = 0.0;  player->dir_y = 1.0;
        player->plane_x = -1.0; player->plane_y = 0.0; // Von -0.66 auf -1.0 erhöht
    }
    else if (dir == 'E') {
        player->dir_x = 1.0;  player->dir_y = 0.0;
        player->plane_x = 0.0;  player->plane_y = 1.0;
    }
    else if (dir == 'W') {
        player->dir_x = -1.0; player->dir_y = 0.0;
        player->plane_x = 0.0;  player->plane_y = -1.0;
    }
}

void    find_spawn_point(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (game->map->map[y])
    {
        x = 0;
        while (game->map->map[y][x])
        {
            if (ft_strchr("NSWE", game->map->map[y][x]))
            {
                // 1. Position auf die Mitte des Tiles setzen
                game->player.pos_x = x + 0.5;
                game->player.pos_y = y + 0.5;
                
                // 2. Blickrichtung setzen
                _set_player_dir(&game->player, game->map->map[y][x]);
                
                // 3. Spawnpunkt in der Map mit Boden ('0') überschreiben
                game->map->map[y][x] = '0';
                return ; // Wir haben den Spawn gefunden, Funktion kann beendet werden
            }
            x++;
        }
        y++;
    }
}

void    draw_player(t_game *game)
{
    int tile_x;
    int tile_y;
    int x;
    int y;

    // Wir runden die genaue Float-Position auf das aktuelle Tile ab
    tile_x = (int)game->player.pos_x;
    tile_y = (int)game->player.pos_y;
    
    y = 0;
    while (y < TILE_SIZE)
    {
        x = 0;
        while (x < TILE_SIZE)
        {
            // Wir zeichnen einen schwarzen Rand und füllen das Tile grün
            if (x == 0 || y == 0 || x == TILE_SIZE - 1 || y == TILE_SIZE - 1)
                put_pixel_to_img(game->img, (tile_x * TILE_SIZE) + x, (tile_y * TILE_SIZE) + y, 0x00000000);
            else
                put_pixel_to_img(game->img, (tile_x * TILE_SIZE) + x, (tile_y * TILE_SIZE) + y, 0x0000FF00);
            x++;
        }
        y++;
    }
}

void    move_player(t_game *game)
{
    double  speed = game->player.move_speed;
    double  rot_speed = game->player.rot_speed;
    double  new_x;
    double  new_y;
    double  old_dir_x;

    // --- 1. BEWEGUNG & KOLLISION ---
    // W: Nach vorne
    if (game->keys[0])
    {
        new_x = game->player.pos_x + game->player.dir_x * speed;
        new_y = game->player.pos_y + game->player.dir_y * speed;
        if (game->map->map[(int)game->player.pos_y][(int)new_x] != '1')
            game->player.pos_x = new_x;
        if (game->map->map[(int)new_y][(int)game->player.pos_x] != '1')
            game->player.pos_y = new_y;
    }
    // S: Nach hinten
    if (game->keys[1])
    {
        new_x = game->player.pos_x - game->player.dir_x * speed;
        new_y = game->player.pos_y - game->player.dir_y * speed;
        if (game->map->map[(int)game->player.pos_y][(int)new_x] != '1')
            game->player.pos_x = new_x;
        if (game->map->map[(int)new_y][(int)game->player.pos_x] != '1')
            game->player.pos_y = new_y;
    }
    // A: Strafing Links
    if (game->keys[2])
    {
        new_x = game->player.pos_x + game->player.dir_y * speed;
        new_y = game->player.pos_y - game->player.dir_x * speed;
        if (game->map->map[(int)game->player.pos_y][(int)new_x] != '1')
            game->player.pos_x = new_x;
        if (game->map->map[(int)new_y][(int)game->player.pos_x] != '1')
            game->player.pos_y = new_y;
    }
    // D: Strafing Rechts
    if (game->keys[3])
    {
        new_x = game->player.pos_x - game->player.dir_y * speed;
        new_y = game->player.pos_y + game->player.dir_x * speed;
        if (game->map->map[(int)game->player.pos_y][(int)new_x] != '1')
            game->player.pos_x = new_x;
        if (game->map->map[(int)new_y][(int)game->player.pos_x] != '1')
            game->player.pos_y = new_y;
    }

	if (game->keys[4]) // Pfeiltaste Links
    {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-rot_speed) - game->player.dir_y * sin(-rot_speed);
        game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y * cos(-rot_speed);
        
        // NEU: Plane mitdrehen
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-rot_speed) - game->player.plane_y * sin(-rot_speed);
        game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y * cos(-rot_speed);
    }
    if (game->keys[5]) // Pfeiltaste Rechts
    {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
        game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);
        
        // NEU: Plane mitdrehen
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
        game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);
    }
}