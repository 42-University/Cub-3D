/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:42 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/04 18:16:00 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	int	i;

	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map.n_texture = NULL;
	game->map.s_texture = NULL;
	game->map.w_texture = NULL;
	game->map.e_texture = NULL;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	i = 0;
	while (i < 3)
	{
		game->map.floor_rgb[i] = -1;
		game->map.ceiling_rgb[i] = -1;
		i++;
	}
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
}

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf(" Error: Wrong number of arguments. Must be .cub\n");
		return (1);
	}
	if (!check_extension(av[1]))
	{
		printf(" Error: Wrong file extension.\n");
		return (1);
	}
	init_game(&game);
	return (0);
}
