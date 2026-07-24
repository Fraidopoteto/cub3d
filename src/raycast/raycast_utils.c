/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 11:14:37 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/16 11:42:27 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

// #include "raycast.h"

// static void	init_delta(t_ray *ray)
// {
// 	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
// 	if (ray->dir_x == 0)
// 		ray->delta_dist_x = 1e30;
// 	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
// 	if (ray->dir_y == 0)
// 		ray->delta_dist_y = 1e30;
// }

// static void	init_step(t_game *game, t_ray *ray)
// {
// 	if (ray->dir_x < 0)
// 	{
// 		ray->step_x = -1;
// 		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
// 	}
// 	else
// 	{
// 		ray->step_x = 1;
// 		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
// 	}

// 	if (ray->dir_y < 0)
// 	{
// 		ray->step_y = -1;
// 		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
// 	}
// 	else
// 	{
// 		ray->step_y = 1;
// 		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
// 	}
// }

// void	setup_ray(t_game *game, t_ray *ray, int x)
// {
// 	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
// 	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
// 	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
// 	ray->map_x = (int)game->player.pos_x;
// 	ray->map_y = (int)game->player.pos_y;

// 	init_delta(ray);
// 	init_step(game, ray);
// }

// static void	calc_line_height(t_ray *ray)
// {
// 	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
// 	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
// 	if (ray->draw_start < 0)
// 		ray->draw_start = 0;
// 	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
// 	if (ray->draw_end >= WIN_HEIGHT)
// 		ray->draw_end = WIN_HEIGHT - 1;
// }

// void	perform_dda(t_game *game, t_ray *ray)
// {
// 	ray->hit = 0;

// 	while (ray->hit == 0)
// 	{
// 		if (ray->side_dist_x < ray->side_dist_y)
// 		{
// 			ray->side_dist_x += ray->delta_dist_x;
// 			ray->map_x += ray->step_x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist_y += ray->delta_dist_y;
// 			ray->map_y += ray->step_y;
// 			ray->side = 1;
// 		}

// 		if (game->map->map[ray->map_y][ray->map_x] == '1')
// 			ray->hit = 1;
// 	}

// 	if (ray->side == 0)
// 		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
// 	else
// 		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;

// 	calc_line_height(ray);
// }