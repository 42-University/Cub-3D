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

static void	dda_step(double *x, double *y, double dx, double dy)
{
	*x += dx;
	*y += dy;
}

static int	map_get(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)map->width || y >= (int)map->height)
		return (1);
	return (map->map[y][x] == '1');
}

int	raycast_column(t_game *game, int x, t_column_info *info)
{
	double	ray_x;
	double	ray_y;
	double	step_x;
	double	step_y;
	int		max_steps;

	ray_x = game->player.x + (game->player.plane_x * (2.0 * x
			/ game->renderer.win_width - 1.0));
	ray_y = game->player.y + (game->player.plane_y * (2.0 * x
			/ game->renderer.win_width - 1.0));
	step_x = (ray_x - game->player.x) * 0.01;
	step_y = (ray_y - game->player.y) * 0.01;
	max_steps = 1000;
	while (max_steps-- > 0)
	{
		dda_step(&ray_x, &ray_y, step_x, step_y);
		if (map_get(&game->map, (int)ray_x, (int)ray_y))
		{
			info->distance = sqrt(pow(ray_x - game->player.x, 2)
					+ pow(ray_y - game->player.y, 2));
			info->face = 0;
			info->tex_offset = 0.0;
			return (1);
		}
	}
	return (0);
}
