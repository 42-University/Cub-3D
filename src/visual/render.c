/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	apply_shade(int color, double dist)
{
	double	shade;
	int		r;
	int		g;
	int		b;

	shade = 1.0 / (1.0 + 0.05 * dist);
	r = (int)(((color >> 16) & 0xFF) * shade);
	g = (int)(((color >> 8) & 0xFF) * shade);
	b = (int)((color & 0xFF) * shade);
	return ((r << 16) | (g << 8) | b);
}

static void	compute_draw(t_game *game, t_column_info *col, t_draw *d)
{
	int	h;

	h = game->renderer.win_height;
	if (col->distance <= 0.0)
		col->distance = 1e-6;
	d->line_height = (int)(h / col->distance);
	if (d->line_height < 1)
		d->line_height = 1;
	d->start = -d->line_height / 2 + h / 2;
	if (d->start < 0)
		d->start = 0;
	d->end = d->line_height / 2 + h / 2;
	if (d->end >= h)
		d->end = h - 1;
}

static void	compute_tex(t_game *game, t_column_info *col, t_draw *d)
{
	t_tex	*tex;
	double	center;

	tex = &game->renderer.textures[col->face];
	d->tex_x = (int)(col->tex_offset * (double)tex->width);
	if (d->tex_x < 0)
		d->tex_x = 0;
	if (d->tex_x >= tex->width)
		d->tex_x = tex->width - 1;
	if (col->flip)
		d->tex_x = tex->width - d->tex_x - 1;
	d->step = (double)tex->height / (double)d->line_height;
	center = d->start - game->renderer.win_height / 2 + d->line_height / 2;
	d->tex_pos = center * d->step;
}

static void	draw_column(t_game *game, int x, t_column_info *col)
{
	t_draw	d;
	t_tex	*tex;
	int		y;
	int		ty;
	int		color;

	compute_draw(game, col, &d);
	compute_tex(game, col, &d);
	tex = &game->renderer.textures[col->face];
	y = d.start;
	while (y <= d.end)
	{
		ty = (int)d.tex_pos;
		if (ty < 0)
			ty = 0;
		if (ty >= tex->height)
			ty = tex->height - 1;
		color = texture_sample(tex, d.tex_x, ty);
		put_pixel(&game->renderer.img, x, y, apply_shade(color, col->distance));
		d.tex_pos += d.step;
		y++;
	}
}

int	render_frame(t_game *game)
{
	int				x;
	t_column_info	col;

	if (game->renderer.should_close)
	{
		mlx_loop_end(game->mlx_ptr);
		return (0);
	}
	movement_update(game);
	fill_background(game);
	x = 0;
	while (x < game->renderer.win_width)
	{
		if (raycast_column(game, x, &col))
			draw_column(game, x, &col);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->renderer.img.img_ptr, 0, 0);
	return (0);
}
