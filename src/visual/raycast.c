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
	if (x >= (int)ft_strlen(map->map[y]))
		return (1);
	return (map->map[y][x] == '1' || map->map[y][x] == ' ');
}

static void	ray_init(t_game *game, t_ray *r, int x)
{
	r->camera_x = 2.0 * x / (double)game->renderer.win_width - 1.0;
	r->ray_dir_x = game->player.dir_x + game->player.plane_x * r->camera_x;
	r->ray_dir_y = game->player.dir_y + game->player.plane_y * r->camera_x;
	r->map_x = (int)game->player.x;
	r->map_y = (int)game->player.y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->ray_dir_y);
}

static void	ray_steps(t_game *game, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->player.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - game->player.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->player.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - game->player.y) * r->delta_dist_y;
	}
}

static void	ray_dda(t_game *game, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map_get(&game->map, r->map_x, r->map_y))
			hit = 1;
	}
}

int	raycast_column(t_game *game, int x, t_column_info *info)
{
	t_ray	r;

	ray_init(game, &r, x);
	ray_steps(game, &r);
	ray_dda(game, &r);
	ray_finish(game, &r, info);
	ray_wall_face(&r, info);
	return (1);
}
