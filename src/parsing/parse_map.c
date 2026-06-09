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

static int	count_map_rows(t_list *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		if (is_map_line((char *)lst->content))
			n++;
		lst = lst->next;
	}
	return (n);
}

void	convert_list_to_matrix(t_game *game)
{
	int		i;
	int		count;
	t_list	*cur;

	count = count_map_rows(game->map_lines);
	game->map.map = malloc(sizeof(char *) * (count + 1));
	if (!game->map.map)
		parse_fatal(game, NULL, "Memory allocation failed.");
	i = 0;
	cur = game->map_lines;
	while (cur)
	{
		if (is_map_line((char *)cur->content))
		{
			game->map.map[i] = ft_strtrim((char *)cur->content, "\n");
			if (!game->map.map[i])
				parse_fatal(game, NULL, "Memory allocation failed.");
			i++;
		}
		cur = cur->next;
	}
	game->map.map[i] = NULL;
}

int	validate_walls(t_game *game)
{
	char	**copy;
	int		result;

	copy = copy_padded_map(game, game->map.width);
	if (!copy)
		parse_fatal(game, NULL, "Memory allocation failed.");
	result = flood_fill(&game->map, copy, (int)game->player.x,
			(int)game->player.y);
	free_matrix(copy);
	return (result);
}

static int	check_config(t_game *game)
{
	if (!game->map.n_texture || !game->map.s_texture
		|| !game->map.w_texture || !game->map.e_texture)
		return (0);
	if (game->map.floor_rgb[0] < 0 || game->map.ceiling_rgb[0] < 0)
		return (0);
	return (1);
}

int	finalize_map(t_game *game)
{
	size_t	width;

	if (!check_config(game))
		return (ft_putendl_fd("Error", 2),
			ft_putendl_fd("Missing or invalid configuration.", 2), 0);
	if (!validade_map_chars(game))
		return (ft_putendl_fd("Error", 2), ft_putendl_fd("Invalid map.", 2), 0);
	if (!scan_map(game, &width))
		return (ft_putendl_fd("Error", 2), ft_putendl_fd("Invalid map.", 2), 0);
	game->map.width = width;
	if (!validate_walls(game))
		return (ft_putendl_fd("Error", 2), ft_putendl_fd("Invalid map.", 2), 0);
	return (1);
}
