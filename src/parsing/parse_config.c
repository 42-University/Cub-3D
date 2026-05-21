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

static void	color_error(char **rgb, char *line)
{
	if (rgb)
		free_matrix(rgb);
	if (line)
		free(line);
	printf("Error\nInvalid color specification.\n");
	exit(1);
}

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
	t_list	*map_lines;

	map_lines = NULL;
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
		if (is_map_line(line) == 1)
			ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	close(fd);
	convert_list_to_matrix(game, map_lines);
	/* compute map dimensions */
	int h = 0;
	size_t w = 0;
	while (game->map.map[h])
	{
		size_t len = ft_strlen(game->map.map[h]);
		if (len > w)
			w = len;
		h++;
	}
	game->map.height = h;
	game->map.width = w;

	/* basic validation of characters */
	if (!validade_map_chars(game))
	{
		printf("Error\nInvalid map.\n");
		exit(1);
	}

	/* find player position and orientation */
	int found = 0;
	for (size_t y = 0; y < game->map.height; y++)
	{
		for (int x = 0; game->map.map[y][x]; x++)
		{
			char c = game->map.map[y][x];
			if (ft_strchr("NSEW", c))
			{
				if (found)
				{
					printf("Error\nInvalid map.\n");
					exit(1);
				}
				found = 1;
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				if (c == 'N')
				{
					game->player.dir_x = 0.0;
					game->player.dir_y = -1.0;
					game->player.plane_x = 0.66;
					game->player.plane_y = 0.0;
				}
				else if (c == 'S')
				{
					game->player.dir_x = 0.0;
					game->player.dir_y = 1.0;
					game->player.plane_x = -0.66;
					game->player.plane_y = 0.0;
				}
				else if (c == 'E')
				{
					game->player.dir_x = 1.0;
					game->player.dir_y = 0.0;
					game->player.plane_x = 0.0;
					game->player.plane_y = 0.66;
				}
				else if (c == 'W')
				{
					game->player.dir_x = -1.0;
					game->player.dir_y = 0.0;
					game->player.plane_x = 0.0;
					game->player.plane_y = -0.66;
				}
				/* replace player char with empty space */
				game->map.map[y][x] = '0';
			}
		}
	}
	if (!found)
	{
		printf("Error\nInvalid map.\n");
		exit(1);
	}

	if (!validate_walls(game))
	{
		printf("Error\nInvalid map.\n");
		exit(1);
	}
}
