/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_load(void *mlx, const char *path, t_tex *texture)
{
	int	width;
	int	height;

	if (!path || !texture)
		return (0);
	texture->img_ptr = mlx_xpm_file_to_image(mlx, (char *)path,
			&width, &height);
	if (!texture->img_ptr)
		return (0);
	texture->pixels = mlx_get_data_addr(texture->img_ptr, &texture->bpp,
			&texture->size_line, &texture->endian);
	texture->width = width;
	texture->height = height;
	return (1);
}

void	texture_free(void *mlx, t_tex *texture)
{
	if (texture && texture->img_ptr && mlx)
	{
		mlx_destroy_image(mlx, texture->img_ptr);
		texture->img_ptr = NULL;
		texture->pixels = NULL;
	}
}

int	texture_sample(t_tex *texture, int x, int y)
{
	char	*dst;

	if (!texture || !texture->pixels)
		return (0);
	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	dst = texture->pixels + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}
