/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:46 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 17:32:24 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_game *game, char **texture, char *line)
{
	int	i;

	if (*texture != NULL)
		parse_fatal(game, line, "Duplicate texture found.");
	i = 2;
	while (line[i] == ' ')
		i++;
	*texture = ft_strtrim(&line[i], " \n");
}

static void	validate_and_save_color(t_game *game, int *color_array,
		char **rgb, char *line)
{
	int	i;

	i = 0;
	while (rgb && rgb[i])
		i++;
	if (i != 3)
		color_error(game, rgb, line);
	i = 0;
	while (i < 3)
	{
		color_array[i] = ft_atoi(rgb[i]);
		if (color_array[i] < 0 || color_array[i] > 255)
			color_error(game, rgb, line);
		i++;
	}
	free_matrix(rgb);
}

void	get_color(t_game *game, int *color_array, char *line)
{
	char	**rgb;
	int		i;

	if (color_array[0] != -1)
		parse_fatal(game, line, "Duplicate color found.");
	i = 1;
	while (line[i] == ' ')
		i++;
	rgb = ft_split(&line[i], ',');
	validate_and_save_color(game, color_array, rgb, line);
}
