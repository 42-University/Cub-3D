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

static int	init_window(t_game *game)
{
	t_renderer	*r;

	r = &game->renderer;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, r->win_width,
			r->win_height, "cub3D");
	if (!game->win_ptr)
		return (0);
	r->img.img_ptr = mlx_new_image(game->mlx_ptr, r->win_width, r->win_height);
	if (!r->img.img_ptr)
		return (0);
	r->img.pixels = mlx_get_data_addr(r->img.img_ptr, &r->img.bpp,
			&r->img.size_line, &r->img.endian);
	r->img.width = r->win_width;
	r->img.height = r->win_height;
	return (1);
}

static void	init_timing(t_game *game)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	game->renderer.last_time = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
}

static int	load_textures(t_game *game)
{
	char	*paths[4];
	int		i;

	paths[0] = game->map.n_texture;
	paths[1] = game->map.s_texture;
	paths[2] = game->map.w_texture;
	paths[3] = game->map.e_texture;
	i = 0;
	while (i < 4)
	{
		if (!texture_load(game->mlx_ptr, paths[i], &game->renderer.textures[i]))
			return (0);
		i++;
	}
	return (1);
}

int	renderer_init(t_game *game)
{
	game->renderer.win_width = 1024;
	game->renderer.win_height = 768;
	game->renderer.should_close = 0;
	if (!init_window(game))
		return (0);
	init_timing(game);
	if (!load_textures(game))
		return (0);
	events_init(game);
	return (1);
}

int	renderer_loop(t_game *game)
{
	mlx_loop_hook(game->mlx_ptr, hook_game(render_frame), game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
