/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:29:57 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 15:13:21 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	color_error(char **rgb, char *line)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("Invalid color format or value.", 2);
	if (rgb)
		free_matrix(rgb);
	free(line);
	exit(1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] != '\0')
	{
		if (ft_strchr(" 01NSEW\n", line[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

void	parse_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		get_texture(&game->map.n_texture, line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		get_texture(&game->map.s_texture, line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		get_texture(&game->map.w_texture, line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		get_texture(&game->map.e_texture, line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		get_color(game->map.floor_rgb, line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		get_color(game->map.ceiling_rgb, line);
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
