/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_y = -1.0;
		p->plane_x = 0.66;
	}
	else if (c == 'S')
	{
		p->dir_y = 1.0;
		p->plane_x = -0.66;
	}
	else if (c == 'E')
	{
		p->dir_x = 1.0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->dir_x = -1.0;
		p->plane_y = -0.66;
	}
}

static void	set_player_state(t_game *game, char c, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
	set_player_dir(&game->player, c);
}

static int	scan_row(t_game *game, int y, int *found)
{
	int	x;

	x = 0;
	while (game->map.map[y][x])
	{
		if (ft_strchr("NSEW", game->map.map[y][x]))
		{
			if (*found)
				return (0);
			*found = 1;
			set_player_state(game, game->map.map[y][x], x, y);
			game->map.map[y][x] = '0';
		}
		x++;
	}
	return (1);
}

int	scan_map(t_game *game, size_t *width)
{
	int		y;
	int		found;
	size_t	len;

	y = 0;
	found = 0;
	*width = 0;
	while (game->map.map[y])
	{
		len = ft_strlen(game->map.map[y]);
		if (len > *width)
			*width = len;
		if (!scan_row(game, y, &found))
			return (0);
		y++;
	}
	game->map.height = y;
	game->map.width = *width;
	return (found);
}
