/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:49 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 17:12:48 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_list_to_matrix(t_game *game, t_list *map_lines)
{
	int		i;
	t_list	*current;
	t_list	*temp;

	game->map.map = malloc(sizeof(char *) * (ft_lstsize(map_lines) + 1));
	if (!game->map.map)
	{
		printf("Error\nMemory allocation failed.\n");
		exit(1);
	}
	i = 0;
	current = map_lines;
	while (current != NULL)
	{
		game->map.map[i++] = (char *)current->content;
		current = current->next;
	}
	game->map.map[i] = NULL;
	while (map_lines != NULL)
	{
		temp = map_lines;
		map_lines = map_lines->next;
		free(temp);
	}
}

int	validade_map_chars(t_game *game)
{
	int	y;
	int	x;
	int	player;

	player = 0;
	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (ft_strchr(" 01NSEW", game->map.map[y][x]) == NULL)
				return (0);
			if (ft_strchr("NSEW", game->map.map[y][x]) != NULL)
				player++;
			x++;
		}
		y++;
	}
	if (player != 1)
		return (0);
	return (1);
}

static int	flood_fill(char **map_copy, int y, int x, int max_y)
{
	if (y < 0 || y >= max_y)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map_copy[y]))
		return (0);
	if (map_copy[y][x] == ' ')
		return (0);
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'X')
		return (1);
	map_copy[y][x] = 'X';
	if (flood_fill(map_copy, y - 1, x, max_y) == 0)
		return (0);
	if (flood_fill(map_copy, y + 1, x, max_y) == 0)
		return (0);
	if (flood_fill(map_copy, y, x - 1, max_y) == 0)
		return (0);
	if (flood_fill(map_copy, y, x + 1, max_y) == 0)
		return (0);
	return (1);
}

int	validate_walls(t_game *game)
{
	char	**map_copy;
	int		max_y;
	int		i;
	int		is_closed;

	max_y = 0;
	while (game->map.map[max_y])
		max_y++;
	map_copy = malloc(sizeof(char *) * (max_y + 1));
	if (!map_copy)
	{
		printf("Error\nMemory allocation failed.\n");
		exit(1);
	}
	i = 0;
	while (i < max_y)
	{
		map_copy[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	map_copy[i] = NULL;
	is_closed = flood_fill(map_copy, game->player.y, game->player.x, max_y);
	free_matrix(map_copy);
	return (is_closed);
}
