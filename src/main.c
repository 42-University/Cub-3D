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
		printf(" Error: Wrong number of arguments. Use --harness or a .cub file\n");
		return (1);
	}
	init_game(&game);
	if (strcmp(av[1], "--harness") == 0 || strcmp(av[1], "harness") == 0)
	{
		/* build a simple map in memory for testing without parser */
		int h = 6;
		char **m = malloc(sizeof(char *) * (h + 1));
		m[0] = strdup("1111111");
		m[1] = strdup("1000001");
		m[2] = strdup("1011101");
		m[3] = strdup("1000101");
		m[4] = strdup("1000001");
		m[5] = strdup("1111111");
		m[6] = NULL;
		game.map.map = m;
		game.map.width = 7;
		game.map.height = h;
		/* colors */
		game.map.floor_rgb[0] = 80;
		game.map.floor_rgb[1] = 80;
		game.map.floor_rgb[2] = 80;
		game.map.ceiling_rgb[0] = 120;
		game.map.ceiling_rgb[1] = 160;
		game.map.ceiling_rgb[2] = 200;
		/* player start */
		game.player.x = 3.5;
		game.player.y = 3.5;
		game.player.dir_x = -1.0;
		game.player.dir_y = 0.0;
		game.player.plane_x = 0.0;
		game.player.plane_y = 0.66;
		/* example textures for harness */
		game.map.n_texture = strdup("textures/north.xpm");
		game.map.s_texture = strdup("textures/south.xpm");
		game.map.w_texture = strdup("textures/west.xpm");
		game.map.e_texture = strdup("textures/east.xpm");
	}
	else
	{
		if (!check_extension(av[1]))
		{
			printf(" Error: Wrong file extension.\n");
			return (1);
		}
		parse_file(&game, av[1]);
	}
	if (!renderer_init(&game))
	{
		printf("Error\nFailed to initialize renderer.\n");
		return (1);
	}
	renderer_loop(&game);
	renderer_destroy(&game);
	return (0);
}
