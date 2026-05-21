/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_get(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)map->width || y >= (int)map->height)
		return (1);
	return (map->map[y][x] == '1');
}

int	raycast_column(t_game *game, int x, t_column_info *info)
{
	double    camera_x;
	double    ray_dir_x;
	double    ray_dir_y;
	int       map_x;
	int       map_y;
	double    side_dist_x;
	double    side_dist_y;
	double    delta_dist_x;
	double    delta_dist_y;
	int       step_x;
	int       step_y;
	int       hit;
	int       side;
	double    perp_dist;
	double    wall_x;

	camera_x = 2.0 * x / (double)game->renderer.win_width - 1.0;
	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1.0 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
	}
	hit = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_get(&game->map, map_x, map_y))
			hit = 1;
	}
	if (side == 0)
		perp_dist = (map_x - game->player.x + (1 - step_x) / 2.0) / ray_dir_x;
	else
		perp_dist = (map_y - game->player.y + (1 - step_y) / 2.0) / ray_dir_y;
	if (side == 0)
		wall_x = game->player.y + perp_dist * ray_dir_y;
	else
		wall_x = game->player.x + perp_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	info->distance = perp_dist;
	info->tex_offset = wall_x;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			info->face = 2; /* west */
		else
			info->face = 3; /* east */
	}
	else
	{
		if (ray_dir_y > 0)
			info->face = 1; /* south */
		else
			info->face = 0; /* north */
	}
	return (1);
}
