/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:46 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/04 20:57:27 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_texture(char **texture, char *line)
{
	int	i;

	if (*texture != NULL)
	{
		printf("Error\nDuplicate texture found.\n");
		free(line);
		exit(1);
	}
	i = 2;
	while (line[i] == ' ')
		i++;
	*texture = ft_strtrim(&line[i], " \n");
}

static void	validate_and_save_color(int *color_array, char **rgb, char *line)
{
	int	i;

	i = 0;
	while (rgb && rgb[i])
		i++;
	if (i != 3)
		color_error(rgb, line);
	i = 0;
	while (i < 3)
	{
		color_array[i] = ft_atoi(rgb[i]);
		if (color_array[i] < 0 || color_array[i] > 255)
			color_error(rgb, line);
		i++;
	}
	free_matrix(rgb);
}

static void	get_color(int *color_array, char *line)
{
	char	**rgb;
	int		i;

	if (color_array[0] != -1)
	{
		printf("Error\nDuplicate color found.\n");
		free(line);
		exit(1);
	}
	i = 1;
	while (line[i] == ' ')
		i++;
	rgb = ft_split(&line[i], ',');
	validate_and_save_color(color_array, rgb, line);
}

static void	parse_line(t_game *game, char *line)
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

void	parse_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open the file.\n");
		exit(1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(game, line);
		printf("%s", line);
		free(line);
	}
	close(fd);
}
