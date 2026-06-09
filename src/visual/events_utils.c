/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_key_state[1024];

int	map_is_wall(t_map *map, double nx, double ny)
{
	const double	radius = 0.18;
	double	sx[4] = {nx + radius, nx - radius, nx + radius, nx - radius};
	double	sy[4] = {ny + radius, ny + radius, ny - radius, ny - radius};
int i;

	i = 0;
	while (i < 4)
	{
		int mx = (int)floor(sx[i]);
		int my = (int)floor(sy[i]);
		if (my < 0 || my >= (int)map->height)
			return (1);
		if (mx < 0)
			return (1);
		if (mx >= (int)ft_strlen(map->map[my]))
			return (1);
		if (map->map[my][mx] == '1' || map->map[my][mx] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	move_forward(t_game *game, double step)
{
	double new_x = game->player.x + game->player.dir_x * step;
	double new_y = game->player.y + game->player.dir_y * step;
	if (!map_is_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (!map_is_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_back(t_game *game, double step)
{
	double new_x = game->player.x - game->player.dir_x * step;
	double new_y = game->player.y - game->player.dir_y * step;
	if (!map_is_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (!map_is_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	strafe_right(t_game *game, double step)
{
	double new_x = game->player.x + game->player.dir_y * step;
	double new_y = game->player.y - game->player.dir_x * step;
	if (!map_is_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (!map_is_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	strafe_left(t_game *game, double step)
{
	double new_x = game->player.x - game->player.dir_y * step;
	double new_y = game->player.y + game->player.dir_x * step;
	if (!map_is_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (!map_is_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	rotate_left(t_game *game, double rot_step)
{
	double old_dx = game->player.dir_x;
	double old_dy = game->player.dir_y;
	double c = cos(rot_step);
	double s = sin(rot_step);
	game->player.dir_x = old_dx * c - old_dy * s;
	game->player.dir_y = old_dx * s + old_dy * c;
	double old_px = game->player.plane_x;
	double old_py = game->player.plane_y;
	game->player.plane_x = old_px * c - old_py * s;
	game->player.plane_y = old_px * s + old_py * c;
}

void	rotate_right(t_game *game, double rot_step)
{
	double old_dx = game->player.dir_x;
	double old_dy = game->player.dir_y;
	double c = cos(-rot_step);
	double s = sin(-rot_step);
	game->player.dir_x = old_dx * c - old_dy * s;
	game->player.dir_y = old_dx * s + old_dy * c;
	double old_px = game->player.plane_x;
	double old_py = game->player.plane_y;
	game->player.plane_x = old_px * c - old_py * s;
	game->player.plane_y = old_px * s + old_py * c;
}
