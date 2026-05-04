/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:46 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/04 18:41:59 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;

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
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (game->map.n_texture != NULL)
			{
				printf("Error\nDuplicate texture for NO.\n");
				free(line);
				exit(1);
			}
			i = 2;
			while (line[i] == ' ')
				i++;
			game->map.n_texture = ft_strtrim(&line[i], " \n");
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (game->map.s_texture != NULL)
			{
				printf("Error\nDuplicate texture for SO.\n");
				free(line);
				exit(1);
			}
			i = 2;
			while(line[i] == ' ')
				i++;
			game->map.s_texture = ft_strtrim(&line[i], " \n");
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (game->map.w_texture != NULL)
			{
				printf("Error\nDuplicate texture for WE.\n");
				free(line);
				exit(1);
			}
			i = 2;
			while(line[i] == ' ')
				i++;
			game->map.w_texture = ft_strtrim(&line[i], " \n");
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (game->map.e_texture != NULL)
			{
				printf("Error\nDuplicate texture for EA.\n");
				free(line);
				exit(1);
			}
			i = 2;
			while (line[i] == ' ')
				i++;
			game->map.e_texture = ft_strtrim(&line[i], " \n");
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			
		}
		printf("%s", line);
		free(line);
	}
	close(fd);
}
