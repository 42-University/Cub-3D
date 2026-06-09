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
	int			i;
	t_list		*current;
	t_list		*next;
	int			count;

	count = ft_lstsize(map_lines);
	game->map.map = malloc(sizeof(char *) * (count + 1));
	if (!game->map.map)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Memory allocation failed.", 2);
		exit(1);
	}
	i = 0;
	current = map_lines;
	while (current)
	{
		game->map.map[i] = current->content;
		next = current->next;
		free(current);
		current = next;
		i++;
	}
	game->map.map[i] = NULL;
}

int	validate_walls(t_game *game)
{
	char	**copy;
	int		result;

	copy = copy_padded_map(game, game->map.width);
	if (!copy)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Memory allocation failed.", 2);
		exit(1);
	}
	result = flood_fill(&game->map, copy, (int)game->player.x,
			(int)game->player.y);
	free_matrix(copy);
	return (result);
}

int	finalize_map(t_game *game)
{
	size_t	width;

	if (!validade_map_chars(game))
		return (ft_putendl_fd("Error", 2), ft_putendl_fd("Invalid map.", 2), 0);
	if (!scan_map(game, &width))
		return (ft_putendl_fd("Error", 2), ft_putendl_fd("Invalid map.", 2), 0);
	game->map.width = width;
	if (!validate_walls(game))
		return (ft_putendl_fd("Error", 2), ft_putendl_fd("Invalid map.", 2), 0);
	return (1);
}
