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

static int	setup_harness_map(t_game *game)
{
	char	**map;

	map = ft_calloc(7, sizeof(char *));
	if (!map)
		return (0);
	map[0] = ft_strdup("1111111");
	map[1] = ft_strdup("1000001");
	map[2] = ft_strdup("1011101");
	map[3] = ft_strdup("1000101");
	map[4] = ft_strdup("1000001");
	map[5] = ft_strdup("1111111");
	if (!map[0] || !map[1] || !map[2] || !map[3] || !map[4] || !map[5])
	{
		free_matrix(map);
		return (0);
	}
	game->map.map = map;
	game->map.width = 7;
	game->map.height = 6;
	return (1);
}

static void	setup_harness_state(t_game *game)
{
	game->map.floor_rgb[0] = 80;
	game->map.floor_rgb[1] = 80;
	game->map.floor_rgb[2] = 80;
	game->map.ceiling_rgb[0] = 120;
	game->map.ceiling_rgb[1] = 160;
	game->map.ceiling_rgb[2] = 200;
	game->player.x = 3.5;
	game->player.y = 3.5;
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->map.n_texture = ft_strdup("textures/north.xpm");
	game->map.s_texture = ft_strdup("textures/south.xpm");
	game->map.w_texture = ft_strdup("textures/west.xpm");
	game->map.e_texture = ft_strdup("textures/east.xpm");
}

static int	launch_game(t_game *game, char *arg)
{
	size_t	len;

	if (strcmp(arg, "--harness") == 0 || strcmp(arg, "harness") == 0)
	{
		if (!setup_harness_map(game))
			return (0);
		setup_harness_state(game);
	}
	else
	{
		len = ft_strlen(arg);
		if (len < 4 || ft_strncmp(arg + len - 4, ".cub", 4) != 0)
		{
			ft_putendl_fd("Error: Wrong file extension.", 2);
			return (0);
		}
		parse_file(game, arg);
	}
	if (!renderer_init(game))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Failed to initialize renderer.", 2);
		return (0);
	}
	renderer_loop(game);
	renderer_destroy(game);
	return (1);
}

void	init_game(t_game *game)
{
	int	i;

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
	t_game	game;

	if (ac != 2)
	{
		ft_putendl_fd("Error: Wrong number of arguments.", 2);
		ft_putendl_fd("Use --harness or a .cub file", 2);
		return (1);
	}
	init_game(&game);
	if (!launch_game(&game, av[1]))
		return (1);
	return (0);
}
