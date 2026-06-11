/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/06/11 16:24:21 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game, double step)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_x * step;
	ny = game->player.y + game->player.dir_y * step;
	if (!map_is_wall(&game->map, nx, game->player.y))
		game->player.x = nx;
	if (!map_is_wall(&game->map, game->player.x, ny))
		game->player.y = ny;
}

void	move_back(t_game *game, double step)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.dir_x * step;
	ny = game->player.y - game->player.dir_y * step;
	if (!map_is_wall(&game->map, nx, game->player.y))
		game->player.x = nx;
	if (!map_is_wall(&game->map, game->player.x, ny))
		game->player.y = ny;
}

void	strafe_right(t_game *game, double step)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_y * step;
	ny = game->player.y - game->player.dir_x * step;
	if (!map_is_wall(&game->map, nx, game->player.y))
		game->player.x = nx;
	if (!map_is_wall(&game->map, game->player.x, ny))
		game->player.y = ny;
}

void	strafe_left(t_game *game, double step)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.dir_y * step;
	ny = game->player.y + game->player.dir_x * step;
	if (!map_is_wall(&game->map, nx, game->player.y))
		game->player.x = nx;
	if (!map_is_wall(&game->map, game->player.x, ny))
		game->player.y = ny;
}

void	movement_update(t_game *game)
{
	double	dt;
	double	move;
	double	rot;

	dt = get_delta_time(game);
	move = 3.0 * dt;
	rot = 2.5 * dt;
	if (game->keys[13])
		move_forward(game, move);
	if (game->keys[1])
		move_back(game, move);
	if (game->keys[0])
		strafe_right(game, move);
	if (game->keys[2])
		strafe_left(game, move);
	if (game->keys[124])
		rotate_left(game, rot);
	if (game->keys[123])
		rotate_right(game, rot);
}
