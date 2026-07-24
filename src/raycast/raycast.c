/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 09:02:34 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/16 11:44:12 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	create_trgb(int *rgb)
{
	if (!rgb)
		return (0);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void	_setup_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
}

static void	_init_delta(t_ray *ray)
{
	ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(1 / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(1 / ray->dir_y);
}

static void	_init_step(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
	}
}

static void	_perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	_draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int				tex_num;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				y;
	int				tex_y;
	char			*src;
	unsigned int	color;
	unsigned int	color_ceiling;
	unsigned int	color_floor;

	color_ceiling = create_trgb(game->map->ceiling_rgb);
	color_floor = create_trgb(game->map->floor_rgb);

	// Textur auswählen
	if (ray->side == 0)
		tex_num = (ray->dir_x > 0) ? 2 : 3;
	else
		tex_num = (ray->dir_y > 0) ? 1 : 0;

	// Wall_x berechnen
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = TEX_WIDTH - tex_x - 1;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_img(game->img, x, y, color_ceiling);
		y++;
	}

	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;

		src = game->texture[tex_num].addr + (tex_y * game->texture[tex_num].line_length
				+ tex_x * (game->texture[tex_num].bits_per_pixel / 8));
		color = *(unsigned int *)src;

		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;

		put_pixel_to_img(game->img, x, y, color);
		y++;
	}

	while (y < WIN_HEIGHT)
	{
		put_pixel_to_img(game->img, x, y, color_floor);
		y++;
	}
}

void	raycast(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		_setup_ray(game, &ray, x);
		_init_delta(&ray);
		_init_step(game, &ray);
		_perform_dda(game, &ray);

		if (ray.side == 0)
			ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;

		ray.line_height = (int)(WIN_HEIGHT / ray.perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + WIN_HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WIN_HEIGHT / 2;
		if (ray.draw_end >= WIN_HEIGHT)
			ray.draw_end = WIN_HEIGHT - 1;

		_draw_wall_column(game, &ray, x);
		x++;
	}
}