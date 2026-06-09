/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_finish(t_game *game, t_ray *r, t_column_info *info)
{
	double	wall_x;

	if (r->side == 0)
		r->perp_dist = (r->map_x - game->player.x
				+ (1 - r->step_x) / 2.0) / r->ray_dir_x;
	else
		r->perp_dist = (r->map_y - game->player.y
				+ (1 - r->step_y) / 2.0) / r->ray_dir_y;
	if (r->side == 0)
		wall_x = game->player.y + r->perp_dist * r->ray_dir_y;
	else
		wall_x = game->player.x + r->perp_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	info->distance = r->perp_dist;
	info->tex_offset = wall_x;
}

void	ray_wall_face(t_ray *r, t_column_info *info)
{
	info->flip = 0;
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			info->face = 2;
		else
			info->face = 3;
	}
	else
	{
		if (r->ray_dir_y > 0)
			info->face = 1;
		else
			info->face = 0;
	}
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		info->flip = 1;
}
