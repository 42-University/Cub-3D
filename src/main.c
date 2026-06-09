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

static int	check_extension(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 4 || ft_strncmp(arg + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static int	launch_game(t_game *game, char *arg)
{
	if (!check_extension(arg))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Wrong file extension.", 2);
		return (0);
	}
	parse_file(game, arg);
	if (!renderer_init(game))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Failed to initialize renderer.", 2);
		return (0);
	}
	renderer_loop(game);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		status;

	if (ac != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (1);
	}
	init_game(&game);
	status = 0;
	if (!launch_game(&game, av[1]))
		status = 1;
	renderer_destroy(&game);
	free_game(&game);
	return (status);
}
