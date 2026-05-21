/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:42 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 17:31:44 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	int i;

	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->renderer.img.img_ptr = NULL;
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

int	main(int ac, char **av)
{
	t_game game;

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
	parse_file(&game, av[1]);
	if (!renderer_init(&game))
	{
		printf("Error\nFailed to initialize renderer.\n");
		return (1);
	}
	renderer_loop(&game);
	renderer_destroy(&game);
	return (0);
}
