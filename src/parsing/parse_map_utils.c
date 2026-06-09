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

static void	set_player_state(t_game *game, char c, int x, int y)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
	if (c == 'N')
	{
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
	}
	else if (c == 'S')
	{
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
	}
	else if (c == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.plane_y = -0.66;
	}
}

static void	free_partial_copy(char **map, size_t rows)
{
	size_t	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	scan_map(t_game *game, size_t *width)
{
	int		y;
	int		x;
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
		x = 0;
		while (game->map.map[y][x])
		{
			if (ft_strchr("NSEW", game->map.map[y][x]))
			{
				if (found)
					return (0);
				found = 1;
				set_player_state(game, game->map.map[y][x], x, y);
				game->map.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	game->map.height = y;
	game->map.width = *width;
	return (found);
}

char	**copy_padded_map(t_game *game, size_t width)
{
	char	**copy;
	size_t	y;
	size_t	x;
	size_t	len;

	copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		copy[y] = malloc(width + 1);
		if (!copy[y])
		{
			free_partial_copy(copy, y);
			return (NULL);
		}
		len = ft_strlen(game->map.map[y]);
		x = 0;
		while (x < width)
		{
			if (x < len)
				copy[y][x] = game->map.map[y][x];
			else
				copy[y][x] = ' ';
			x++;
		}
		copy[y][x] = '\0';
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

int	flood_fill(t_map *map, char **grid, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if ((size_t)x >= map->width || (size_t)y >= map->height)
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'F')
		return (1);
	if (grid[y][x] == ' ' || grid[y][x] == '\0')
		return (0);
	grid[y][x] = 'F';
	if (!flood_fill(map, grid, x + 1, y))
		return (0);
	if (!flood_fill(map, grid, x - 1, y))
		return (0);
	if (!flood_fill(map, grid, x, y + 1))
		return (0);
	if (!flood_fill(map, grid, x, y - 1))
		return (0);
	return (1);
}