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

/* g_key_state is defined in events_utils.c */

typedef int (*t_mlx_hook)();

static t_mlx_hook	get_key_press_hook(void);
static t_mlx_hook	get_key_release_hook(void);

static int	map_key(int keycode)
{
    /* Support both macOS and Linux (X11) keycodes */
	if (keycode == 65307 || keycode == 53) /* ESC */
		return (53);
	if (keycode == 65361 || keycode == 123) /* left */
		return (123);
	if (keycode == 65363 || keycode == 124) /* right */
		return (124);
	if (keycode == 'w' /*119*/ || keycode == 13) /* forward */
		return (13);
	if (keycode == 's' /*115*/ || keycode == 1) /* back */
		return (1);
	if (keycode == 'a' /*97*/ || keycode == 0) /* strafe left */
		return (0);
	if (keycode == 'd' /*100*/ || keycode == 2) /* strafe right */
		return (2);
	return (keycode);
}

static int	on_key_press(int keycode, t_game *game)
{
	int k = map_key(keycode);
	void	movement_update(t_game *game)
	{
	const double move_speed_per_s = 3.0;
	const double rot_speed_per_s = 2.5;
	struct timeval tv;
	double now;
	double dt;

	gettimeofday(&tv, NULL);
	now = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	if (game->renderer.last_time <= 0.0)
	dt = 0.016;
	else
	dt = now - game->renderer.last_time;
	if (dt <= 0.0 || dt > 0.5)
	dt = 0.016;
	game->renderer.last_time = now;

	double move_step = move_speed_per_s * dt;
	double rot_step = rot_speed_per_s * dt;

	if (g_key_state[13])
		move_forward(game, move_step);
	if (g_key_state[1])
		move_back(game, move_step);
	if (g_key_state[2])
		strafe_right(game, move_step);
	if (g_key_state[0])
		strafe_left(game, move_step);
	if (g_key_state[123])
		rotate_left(game, rot_step);
	if (g_key_state[124])
		rotate_right(game, rot_step);
	}
	now = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	if (game->renderer.last_time <= 0.0)
		dt = 0.016;
	else
		dt = now - game->renderer.last_time;
	if (dt <= 0.0 || dt > 0.5)
		dt = 0.016;
	game->renderer.last_time = now;

	double move_step = move_speed_per_s * dt;
	double rot_step = rot_speed_per_s * dt;

    /* forward (W) */
	if (g_key_state[13])
	{
		new_x = game->player.x + game->player.dir_x * move_step;
		new_y = game->player.y + game->player.dir_y * move_step;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
    /* back (S) */
	if (g_key_state[1])
	{
		new_x = game->player.x - game->player.dir_x * move_step;
		new_y = game->player.y - game->player.dir_y * move_step;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
    /* strafe right (D) */
	if (g_key_state[2])
	{
		new_x = game->player.x + game->player.dir_y * move_step;
		new_y = game->player.y - game->player.dir_x * move_step;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
    /* strafe left (A) */
	if (g_key_state[0])
	{
		new_x = game->player.x - game->player.dir_y * move_step;
		new_y = game->player.y + game->player.dir_x * move_step;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
    /* rotate left */
	if (g_key_state[123])
	{
		double old_dir_x = game->player.dir_x;
		double old_dir_y = game->player.dir_y;
		double c = cos(rot_step);
		double s = sin(rot_step);
		game->player.dir_x = old_dir_x * c - old_dir_y * s;
		game->player.dir_y = old_dir_x * s + old_dir_y * c;
		double old_plane_x = game->player.plane_x;
		double old_plane_y = game->player.plane_y;
		game->player.plane_x = old_plane_x * c - old_plane_y * s;
		game->player.plane_y = old_plane_x * s + old_plane_y * c;
	}
    /* rotate right */
	if (g_key_state[124])
	{
		double old_dir_x = game->player.dir_x;
		double old_dir_y = game->player.dir_y;
		double c = cos(-rot_step);
		double s = sin(-rot_step);
		game->player.dir_x = old_dir_x * c - old_dir_y * s;
		game->player.dir_y = old_dir_x * s + old_dir_y * c;
		double old_plane_x = game->player.plane_x;
		double old_plane_y = game->player.plane_y;
		game->player.plane_x = old_plane_x * c - old_plane_y * s;
		game->player.plane_y = old_plane_x * s + old_plane_y * c;
	}
}
