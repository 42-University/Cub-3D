/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:46 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 17:32:24 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	read_all_lines(t_game *game, int fd)
{
	char	*line;
	t_list	*node;

	line = get_next_line(fd);
	while (line)
	{
		node = ft_lstnew(line);
		if (!node)
			parse_fatal(game, line, "Memory allocation failed.");
		ft_lstadd_back(&game->map_lines, node);
		line = get_next_line(fd);
	}
}

static void	process_config(t_game *game)
{
	t_list	*cur;

	cur = game->map_lines;
	while (cur)
	{
		parse_line(game, (char *)cur->content);
		cur = cur->next;
	}
}

void	parse_file(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_fatal(game, NULL, "Could not open the file.");
	read_all_lines(game, fd);
	close(fd);
	process_config(game);
	convert_list_to_matrix(game);
	ft_lstclear(&game->map_lines, free);
	if (!finalize_map(game))
	{
		free_game(game);
		exit(1);
	}
}
