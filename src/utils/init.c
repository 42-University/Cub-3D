/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:42 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 17:31:44 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_renderer(t_game *game)
{
	int	i;

	game->renderer.img.img_ptr = NULL;
	i = 0;
	while (i < 4)
	{
		game->renderer.textures[i].img_ptr = NULL;
		game->renderer.textures[i].pixels = NULL;
		i++;
	}
	i = 0;
	while (i < 1024)
	{
		game->keys[i] = 0;
		i++;
	}
}

static void	init_map_fields(t_game *game)
{
	int	i;

	game->map.n_texture = NULL;
	game->map.s_texture = NULL;
	game->map.w_texture = NULL;
	game->map.e_texture = NULL;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	i = 0;
	while (i < 3)
	{
		game->map.floor_rgb[i] = -1;
		game->map.ceiling_rgb[i] = -1;
		i++;
	}
}

static void	init_player(t_game *game)
{
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
}

void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map_lines = NULL;
	game->renderer.should_close = 0;
	game->renderer.last_time = 0.0;
	init_renderer(game);
	init_map_fields(game);
	init_player(game);
}
