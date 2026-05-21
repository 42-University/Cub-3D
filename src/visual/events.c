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

/* larger key table to accommodate X11 keycodes mapping */
static int	g_key_state[1024];

static int	map_key(int keycode)
{
	/* map common X11 keycodes to small indices used below */
	if (keycode == 65307) /* ESC X11 */
		return (53);
	if (keycode == 65361) /* left */
		return (123);
	if (keycode == 65363) /* right */
		return (124);
	if (keycode == 'w' /*119*/)
		return (13);
	if (keycode == 's' /*115*/)
		return (1);
	if (keycode == 'a' /*97*/)
		return (0);
	if (keycode == 'd' /*100*/)
		return (2);
	return (keycode);
}

static int	on_key_press(int keycode, t_game *game)
{
	int k = map_key(keycode);
	if (k >= 0 && k < 1024)
		g_key_state[k] = 1;
	if (k == 53)
		game->renderer.should_close = 1;
	return (0);
}

static int	on_key_release(int keycode, t_game *game)
{
	int k = map_key(keycode);
	if (k >= 0 && k < 1024)
		g_key_state[k] = 0;
	(void)game;
	return (0);
}

int	events_init(t_game *game)
{
	int i;

	i = 0;
	while (i < 1024)
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

static int	map_is_wall(t_map *map, double nx, double ny)
{
	/* treat player as a small circle to avoid clipping into walls */
	const double radius = 0.18;
	double sx[4] = {nx + radius, nx - radius, nx + radius, nx - radius};
	double sy[4] = {ny + radius, ny + radius, ny - radius, ny - radius};
	int i;

	i = 0;
	while (i < 4)
	{
		int mx = (int)floor(sx[i]);
		int my = (int)floor(sy[i]);
		if (my < 0 || my >= (int)map->height)
			return (1);
		if (mx < 0)
			return (1);
		if (mx >= (int)ft_strlen(map->map[my]))
			return (1);
		if (map->map[my][mx] == '1' || map->map[my][mx] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	movement_update(t_game *game)
{
	double move_speed = 0.08;
	double rot_speed = 0.06;
	double new_x;
	double new_y;

	/* forward (W) */
	if (g_key_state[13])
	{
		new_x = game->player.x + game->player.dir_x * move_speed;
		new_y = game->player.y + game->player.dir_y * move_speed;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
	/* back (S) */
	if (g_key_state[1])
	{
		new_x = game->player.x - game->player.dir_x * move_speed;
		new_y = game->player.y - game->player.dir_y * move_speed;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
	/* strafe right (D) */
	if (g_key_state[2])
	{
		new_x = game->player.x + game->player.dir_y * move_speed;
		new_y = game->player.y - game->player.dir_x * move_speed;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
	/* strafe left (A) */
	if (g_key_state[0])
	{
		new_x = game->player.x - game->player.dir_y * move_speed;
		new_y = game->player.y + game->player.dir_x * move_speed;
		if (!map_is_wall(&game->map, new_x, game->player.y))
			game->player.x = new_x;
		if (!map_is_wall(&game->map, game->player.x, new_y))
			game->player.y = new_y;
	}
	/* rotate left */
	if (g_key_state[123])
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rot_speed) - game->player.dir_y * sin(rot_speed);
		game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y * cos(rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rot_speed) - game->player.plane_y * sin(rot_speed);
		game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y * cos(rot_speed);
	}
	/* rotate right */
	if (g_key_state[124])
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot_speed) - game->player.dir_y * sin(-rot_speed);
		game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y * cos(-rot_speed);
		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot_speed) - game->player.plane_y * sin(-rot_speed);
		game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y * cos(-rot_speed);
	}
}
