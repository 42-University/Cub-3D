/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->pixels + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical_line(t_game *game, int x, int height, int color)
{
	int	y;
	int	start;

	if (height > game->renderer.win_height)
		height = game->renderer.win_height;
	start = (game->renderer.win_height - height) / 2;
	y = start;
	while (y < start + height)
	{
		put_pixel(&game->renderer.img, x, y, color);
		y++;
	}
}

void	fill_background(t_game *game)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = (game->map.floor_rgb[0] << 16)
		| (game->map.floor_rgb[1] << 8) | game->map.floor_rgb[2];
	ceiling_color = (game->map.ceiling_rgb[0] << 16)
		| (game->map.ceiling_rgb[1] << 8) | game->map.ceiling_rgb[2];
	y = 0;
	while (y < game->renderer.win_height)
	{
		x = 0;
		while (x < game->renderer.win_width)
		{
			if (y < game->renderer.win_height / 2)
				put_pixel(&game->renderer.img, x, y, ceiling_color);
			else
				put_pixel(&game->renderer.img, x, y, floor_color);
			x++;
		}
		y++;
	}
}
