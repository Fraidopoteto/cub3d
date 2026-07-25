/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:18:29 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 12:26:17 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int load_xpm_texture(t_game *game, t_img *tex, char *path)
{
    tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img_ptr)
        return (1);
    tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
            &tex->line_length, &tex->endian);
    return (0);
}

static int init_textures(t_game *game)
{
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
    game->player.move_speed = 0.05;
    game->player.rot_speed = 0.05;
    find_spawn_point(game);
    init_textures(game);
}
