/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_key(int keycode)
{
	if (keycode == 65307 || keycode == 53)
		return (53);
	if (keycode == 65361 || keycode == 123)
		return (123);
	if (keycode == 65363 || keycode == 124)
		return (124);
	if (keycode == 'w' || keycode == 13)
		return (13);
	if (keycode == 's' || keycode == 1)
		return (1);
	if (keycode == 'a' || keycode == 0)
		return (0);
	if (keycode == 'd' || keycode == 2)
		return (2);
	return (-1);
}

static int	on_key_press(int keycode, t_game *game)
{
	int	k;

	k = map_key(keycode);
	if (k == 53)
		game->renderer.should_close = 1;
	else if (k >= 0 && k < 1024)
		game->keys[k] = 1;
	return (0);
}

static int	on_key_release(int keycode, t_game *game)
{
	int	k;

	k = map_key(keycode);
	if (k >= 0 && k < 1024)
		game->keys[k] = 0;
	return (0);
}

static int	on_close(t_game *game)
{
	game->renderer.should_close = 1;
	return (0);
}

int	events_init(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx_ptr);
	mlx_hook(game->win_ptr, 2, 1L << 0, hook_key(on_key_press), game);
	mlx_hook(game->win_ptr, 3, 1L << 1, hook_key(on_key_release), game);
	mlx_hook(game->win_ptr, 17, 1L << 17, hook_game(on_close), game);
	return (1);
}
