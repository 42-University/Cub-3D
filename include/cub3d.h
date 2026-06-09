/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:04:56 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 17:06:12 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
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
	double	last_time;
}			t_renderer;

typedef struct s_column_info
{
	double	distance;
	int		face;
	double	tex_offset;
	int		flip;
}			t_column_info;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	void		*mlx_ptr;
	void		*win_ptr;
	t_renderer	renderer;
	int			keys[1024];
	t_list		*map_lines;
}				t_game;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
}			t_ray;

typedef struct s_draw
{
	int		line_height;
	int		start;
	int		end;
	int		tex_x;
	double	step;
	double	tex_pos;
}			t_draw;

typedef int	(*t_hook)(void);

typedef union u_game_hook
{
	t_hook	generic;
	int		(*typed)(t_game *);
}			t_game_hook;

typedef union u_key_hook
{
	t_hook	generic;
	int		(*typed)(int, t_game *);
}			t_key_hook;

/* main / init / cleanup */
void			init_game(t_game *game);
void			free_game(t_game *game);
void			renderer_destroy(t_game *game);

/* renderer / render */
int				renderer_init(t_game *game);
int				renderer_loop(t_game *game);
int				render_frame(t_game *game);

/* hooks (function-pointer type laundering for mlx) */
t_hook			hook_game(int (*f)(t_game *));
t_hook			hook_key(int (*f)(int, t_game *));

/* raycast */
int				raycast_column(t_game *game, int x, t_column_info *info);
void			ray_finish(t_game *game, t_ray *r, t_column_info *info);
void			ray_wall_face(t_ray *r, t_column_info *info);

/* draw */
void			put_pixel(t_img *img, int x, int y, int color);
void			fill_background(t_game *game);

/* texture */
int				texture_load(void *mlx, const char *path, t_tex *texture);
void			texture_free(void *mlx, t_tex *texture);
int				texture_sample(t_tex *texture, int x, int y);

/* events / movement */
int				events_init(t_game *game);
void			movement_update(t_game *game);
double			get_delta_time(t_game *game);
int				map_is_wall(t_map *map, double nx, double ny);
void			move_forward(t_game *game, double step);
void			move_back(t_game *game, double step);
void			strafe_right(t_game *game, double step);
void			strafe_left(t_game *game, double step);
void			rotate_left(t_game *game, double rot_step);
void			rotate_right(t_game *game, double rot_step);

/* parsing utils */
void			free_matrix(char **matrix);
void			parse_fatal(t_game *game, char *line, char *msg);
void			color_error(t_game *game, char **rgb, char *line);
int				is_map_line(char *line);
void			parse_line(t_game *game, char *line);
void			get_texture(t_game *game, char **texture, char *line);
void			get_color(t_game *game, int *color_array, char *line);

/* parsing */
void			parse_file(t_game *game, char *filename);
void			convert_list_to_matrix(t_game *game);
int				scan_map(t_game *game, size_t *width);
char			**copy_padded_map(t_game *game, size_t width);
int				flood_fill(t_map *map, char **grid, int x, int y);
int				validade_map_chars(t_game *game);
int				finalize_map(t_game *game);
int				validate_walls(t_game *game);

#endif
