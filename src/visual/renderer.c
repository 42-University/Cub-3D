/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		game->renderer.should_close = 1;
	return (0);
}

static int	on_close(t_game *game)
{
	game->renderer.should_close = 1;
	return (0);
}

static int	render_frame(t_game *game)
{
	int				x;
	t_column_info	col;
	if (game->renderer.should_close)
		return (0);
	movement_update(game);
	fill_background(game);
	x = 0;
	while (x < game->renderer.win_width)
	{
		if (raycast_column(game, x, &col))
		{
			int line_height;
			int draw_start;
			int draw_end;
			t_tex *tex;
			int tex_x;
			double step_tex;
			double tex_pos;
			int y;

			if (col.distance <= 0.0)
				col.distance = 1e-6;
			line_height = (int)(game->renderer.win_height / col.distance);
			if (line_height < 1)
				line_height = 1;
			draw_start = -line_height / 2 + game->renderer.win_height / 2;
			if (draw_start < 0)
				draw_start = 0;
			draw_end = line_height / 2 + game->renderer.win_height / 2;
			if (draw_end >= game->renderer.win_height)
				draw_end = game->renderer.win_height - 1;

			tex = &game->renderer.textures[col.face];
			if (tex && tex->pixels && tex->width > 0 && tex->height > 0)
			{
				tex_x = (int)(col.tex_offset * (double)tex->width);
				if (tex_x < 0)
					tex_x = 0;
				if (tex_x >= tex->width)
					tex_x = tex->width - 1;
				if (col.flip)
				{
					tex_x = tex->width - tex_x - 1;
					if (tex_x < 0)
						tex_x = 0;
				}
				step_tex = (double)tex->height / (double)line_height;
				tex_pos = (draw_start - game->renderer.win_height / 2 + line_height / 2) * step_tex;
				y = draw_start;
				while (y <= draw_end)
				{
					int tex_y = (int)tex_pos;
					if (tex_y < 0)
						tex_y = 0;
					if (tex_y >= tex->height)
						tex_y = tex->height - 1;
					int sample = texture_sample(tex, tex_x, tex_y);
					double shade = 1.0 / (1.0 + 0.05 * col.distance);
					int r = (int)((((sample >> 16) & 0xFF)) * shade);
					int g = (int)((((sample >> 8) & 0xFF)) * shade);
					int b = (int)(((sample & 0xFF)) * shade);
					int color = (r << 16) | (g << 8) | b;
					put_pixel(&game->renderer.img, x, y, color);
					tex_pos += step_tex;
					y++;
				}
			}
			else
			{
				/* fallback to solid color per face with shading */
				int color;
				double shade;

				if (col.face == 0)
					color = 0xFF0000;
				else if (col.face == 1)
					color = 0x00FF00;
				else if (col.face == 2)
					color = 0x0000FF;
				else
					color = 0xFFFF00;
				shade = 1.0 / (1.0 + 0.05 * col.distance);
				int rr = (int)(((color >> 16) & 0xFF) * shade);
				int gg = (int)(((color >> 8) & 0xFF) * shade);
				int bb = (int)((color & 0xFF) * shade);
				color = (rr << 16) | (gg << 8) | bb;
				int yy = draw_start;
				while (yy <= draw_end)
				{
					put_pixel(&game->renderer.img, x, yy, color);
					yy++;
				}
			}
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->renderer.img.img_ptr, 0, 0);
	return (0);
}

int	renderer_init(t_game *game)
{
	game->renderer.win_width = 1024;
	game->renderer.win_height = 768;
	game->renderer.should_close = 0;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->renderer.win_width,
			game->renderer.win_height, "cub3D");
	if (!game->win_ptr)
		return (0);
	game->renderer.img.img_ptr = mlx_new_image(game->mlx_ptr,
			game->renderer.win_width, game->renderer.win_height);
	if (!game->renderer.img.img_ptr)
		return (0);
	game->renderer.img.pixels = mlx_get_data_addr(game->renderer.img.img_ptr,
			&game->renderer.img.bpp, &game->renderer.img.size_line,
			&game->renderer.img.endian);
	game->renderer.img.width = game->renderer.win_width;
	game->renderer.img.height = game->renderer.win_height;
	/* initialize timing for delta-time movement */
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		game->renderer.last_time = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	}
	if (!events_init(game))
		return (0);
	/* load textures if paths are provided */
	{
		const char *paths[4] = {game->map.n_texture, game->map.s_texture,
			game->map.w_texture, game->map.e_texture};
		int i;

		i = 0;
		while (i < 4)
		{
			game->renderer.textures[i].img_ptr = NULL;
			game->renderer.textures[i].pixels = NULL;
			game->renderer.textures[i].width = 0;
			game->renderer.textures[i].height = 0;
			if (paths[i])
				texture_load(game->mlx_ptr, paths[i], &game->renderer.textures[i]);
			i++;
		}
	}
	return (1);
}

int	renderer_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, (int (*)(int, void *))on_key_press,
		game);
	mlx_hook(game->win_ptr, 17, 1L << 0, (int (*)(void *))on_close, game);
	mlx_loop_hook(game->mlx_ptr, (int (*)(void *))render_frame, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}

void	renderer_destroy(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		texture_free(game->mlx_ptr, &game->renderer.textures[i]);
		i++;
	}
	if (game->renderer.img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->renderer.img.img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
}
