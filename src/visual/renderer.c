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
	fill_background(game);
	x = 0;
	while (x < game->renderer.win_width)
	{
		if (raycast_column(game, x, &col))
			draw_vertical_line(game, x, game->renderer.win_height, 0xFFFFFF);
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
	if (!events_init(game))
		return (0);
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
