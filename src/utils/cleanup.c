/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:13:42 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 17:31:44 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	renderer_destroy(t_game *game)
{
	int	i;

	if (game->mlx_ptr)
		mlx_do_key_autorepeaton(game->mlx_ptr);
	i = 0;
	while (i < 4)
	{
		texture_free(game->mlx_ptr, &game->renderer.textures[i]);
		i++;
	}
	if (game->renderer.img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->renderer.img.img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	parse_fatal(t_game *game, char *line, char *msg)
{
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	free(line);
	free_game(game);
	exit(1);
}

void	free_game(t_game *game)
{
	if (game->map_lines)
		ft_lstclear(&game->map_lines, free);
	free(game->map.n_texture);
	free(game->map.s_texture);
	free(game->map.w_texture);
	free(game->map.e_texture);
	free_matrix(game->map.map);
}
