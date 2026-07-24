/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:18:29 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/13 10:17:54 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int load_xpm_texture(t_game *game, t_img *tex, char *path)
{
    tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img_ptr)
        return (1); // Fehler beim Laden
    tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
            &tex->line_length, &tex->endian);
    return (0);
}

// Diese Funktion rufst du am Ende deiner init() Funktion auf
static int init_textures(t_game *game)
{
    // Hier testweise feste Pfade, später kommen die aus deinem Parser!
    if (load_xpm_texture(game, &game->texture[0], game->map->path_no) ||
        load_xpm_texture(game, &game->texture[1], game->map->path_so) ||
        load_xpm_texture(game, &game->texture[2], game->map->path_ea) ||
        load_xpm_texture(game, &game->texture[3], game->map->path_we))
    {
        ft_putstr_fd("Error\nFailed to load textures\n", 2);
        exit(1);
    }
    return (0);
}

void    init(t_game *game)
{
    // --- MLX Setup ---
    game->mlx = mlx_init();
    if (!game->mlx)
        exit(1);
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game->win)
        return ;
    game->img->img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!game->img->img_ptr)
        return ;
    game->img->addr = mlx_get_data_addr(game->img->img_ptr,
            &game->img->bits_per_pixel,
            &game->img->line_length,
            &game->img->endian);

    // --- Player Setup ---
    // Geschwindigkeiten setzen
    game->player.move_speed = 0.05;
    game->player.rot_speed = 0.05;

    // NEU: Map durchsuchen und Player dynamisch platzieren
    find_spawn_point(game);
    init_textures(game);
}
