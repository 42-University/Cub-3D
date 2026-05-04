/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:04:56 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/04 18:17:34 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"

typedef struct s_map
{
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	**map;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	size_t	width;
	size_t	height;
}			t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_tex
{
	void	*img_ptr;
	char	*pixels;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_tex;

typedef struct s_renderer
{
	t_img	img;
	t_tex	textures[4];
	int		win_width;
	int		win_height;
	int		should_close;
}			t_renderer;

typedef struct s_column_info
{
	double	distance;
	int		face;
	double	tex_offset;
}			t_column_info;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	void		*mlx_ptr;
	void		*win_ptr;
	t_renderer	renderer;
}				t_game;

int				renderer_init(t_game *game);
int				renderer_loop(t_game *game);
void			renderer_destroy(t_game *game);
int				raycast_column(t_game *game, int x, t_column_info *info);
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_vertical_line(t_game *game, int x, int height, int color);
void			fill_background(t_game *game);
int				texture_load(void *mlx, const char *path, t_tex *texture);
void			texture_free(void *mlx, t_tex *texture);
int				texture_sample(t_tex *texture, int x, int y);
int				events_init(t_game *game);
void			movement_update(t_game *game);

#endif