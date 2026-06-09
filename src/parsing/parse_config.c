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

void	get_texture(char **texture, char *line)
{
	int	i;

	if (*texture != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Duplicate texture found.", 2);
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

void	get_color(int *color_array, char *line)
{
	char	**rgb;
	int		i;

	if (color_array[0] != -1)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Duplicate color found.", 2);
		free(line);
		exit(1);
	}
	i = 1;
	while (line[i] == ' ')
		i++;
	rgb = ft_split(&line[i], ',');
	validate_and_save_color(color_array, rgb, line);
}

static void	load_map_lines(t_game *game, int fd, t_list **map_lines)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(game, line);
		if (is_map_line(line) == 1)
			ft_lstadd_back(map_lines, ft_lstnew(ft_strdup(line)));
		free(line);
	}
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
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Could not open the file.", 2);
		exit(1);
	}
	load_map_lines(game, fd, &map_lines);
	close(fd);
	convert_list_to_matrix(game, map_lines);
	if (!finalize_map(game))
		exit(1);
}
