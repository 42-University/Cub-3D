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

static int	g_key_state[256];

static int	on_key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		g_key_state[keycode] = 1;
	if (keycode == 53)
		game->renderer.should_close = 1;
	return (0);
}

static int	on_key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		g_key_state[keycode] = 0;
	(void)game;
	return (0);
}

int	events_init(t_game *game)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		g_key_state[i] = 0;
		i++;
	}
	mlx_hook(game->win_ptr, 2, 1L << 0, (int (*)(int, void *))on_key_press,
		game);
	mlx_hook(game->win_ptr, 3, 1L << 1, (int (*)(int, void *))on_key_release,
		game);
	return (1);
}

void	movement_update(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.05;
	if (g_key_state[13])
	{
		game->player.x += game->player.dir_x * move_speed;
		game->player.y += game->player.dir_y * move_speed;
	}
	if (g_key_state[1])
	{
		game->player.x -= game->player.dir_x * move_speed;
		game->player.y -= game->player.dir_y * move_speed;
	}
	if (g_key_state[0])
	{
		game->player.x += game->player.dir_y * move_speed;
		game->player.y -= game->player.dir_x * move_speed;
	}
	if (g_key_state[2])
	{
		game->player.x -= game->player.dir_y * move_speed;
		game->player.y += game->player.dir_x * move_speed;
	}
}
