/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	fill_row(char *dst, char *src, size_t width)
{
	size_t	len;
	size_t	x;

	len = ft_strlen(src);
	x = 0;
	while (x < width)
	{
		if (x < len)
			dst[x] = src[x];
		else
			dst[x] = ' ';
		x++;
	}
	dst[x] = '\0';
}

char	**copy_padded_map(t_game *game, size_t width)
{
	char	**copy;
	size_t	y;

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
		fill_row(copy[y], game->map.map[y], width);
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
