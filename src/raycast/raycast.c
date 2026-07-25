/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 09:02:34 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:11:06 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	_calc_line_height(t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
}

static void	_calc_tex(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->tex_num = (r->dir_x > 0) ? 2 : 3;
	else
		r->tex_num = (r->dir_y > 0) ? 1 : 0;
	if (r->side == 0)
		r->wall_x = g->player.pos_y + r->perp_wall_dist * r->dir_y;
	else
		r->wall_x = g->player.pos_x + r->perp_wall_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEX_WIDTH);
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	r->step = 1.0 * TEX_HEIGHT / r->line_height;
	r->tex_pos = (r->draw_start - WIN_HEIGHT / 2
			+ r->line_height / 2) * r->step;
}

static void	_draw_pixels(t_game *g, t_ray *r, int x)
{
	int				y;
	int				t_y;
	char			*src;
	unsigned int	c;

	y = -1;
	while (++y < r->draw_start)
		put_pixel_to_img(g->img, x, y, r->c_color);
	y--;
	while (++y < r->draw_end)
	{
		t_y = (int)r->tex_pos & (TEX_HEIGHT - 1);
		r->tex_pos += r->step;
		src = g->texture[r->tex_num].addr + (t_y
				* g->texture[r->tex_num].line_length + r->tex_x
				* (g->texture[r->tex_num].bits_per_pixel / 8));
		c = *(unsigned int *)src;
		if (r->side == 1)
			c = (c >> 1) & 0x7F7F7F;
		put_pixel_to_img(g->img, x, y, c);
	}
	y--;
	while (++y < WIN_HEIGHT)
		put_pixel_to_img(g->img, x, y, r->f_color);
}

void	raycast(t_game *g)
{
	int		x;
	t_ray	r;

	r.c_color = create_trgb(g->map->ceiling_rgb);
	r.f_color = create_trgb(g->map->floor_rgb);
	x = 0;
	while (x < WIN_WIDTH)
	{
		setup_ray(g, &r, x);
		perform_dda(g, &r);
		_calc_line_height(&r);
		_calc_tex(g, &r);
		_draw_pixels(g, &r, x);
		x++;
	}
}
