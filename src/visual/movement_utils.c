/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_delta_time(t_game *game)
{
	struct timeval	tv;
	double			now;
	double			dt;

	gettimeofday(&tv, NULL);
	now = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	dt = now - game->renderer.last_time;
	if (game->renderer.last_time <= 0.0 || dt <= 0.0 || dt > 0.5)
		dt = 0.016;
	game->renderer.last_time = now;
	return (dt);
}

int	map_is_wall(t_map *map, double nx, double ny)
{
	int	mx;
	int	my;

	mx = (int)floor(nx);
	my = (int)floor(ny);
	if (my < 0 || my >= (int)map->height || mx < 0)
		return (1);
	if (mx >= (int)ft_strlen(map->map[my]))
		return (1);
	if (map->map[my][mx] == '1' || map->map[my][mx] == ' ')
		return (1);
	return (0);
}

void	rotate_left(t_game *game, double rot_step)
{
	double	dx;
	double	px;
	double	c;
	double	s;

	c = cos(rot_step);
	s = sin(rot_step);
	dx = game->player.dir_x;
	game->player.dir_x = dx * c - game->player.dir_y * s;
	game->player.dir_y = dx * s + game->player.dir_y * c;
	px = game->player.plane_x;
	game->player.plane_x = px * c - game->player.plane_y * s;
	game->player.plane_y = px * s + game->player.plane_y * c;
}

void	rotate_right(t_game *game, double rot_step)
{
	double	dx;
	double	px;
	double	c;
	double	s;

	c = cos(-rot_step);
	s = sin(-rot_step);
	dx = game->player.dir_x;
	game->player.dir_x = dx * c - game->player.dir_y * s;
	game->player.dir_y = dx * s + game->player.dir_y * c;
	px = game->player.plane_x;
	game->player.plane_x = px * c - game->player.plane_y * s;
	game->player.plane_y = px * s + game->player.plane_y * c;
}
