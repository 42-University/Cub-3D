/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:29:57 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/07 15:13:21 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	color_error(char **rgb, char *line)
{
	printf("Error\nInvalid color format or value.\n");
	if (rgb)
		free_matrix(rgb);
	free(line);
	exit(1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] != '\0')
	{
		if (ft_strchr(" 01NSEW\n", line[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

int	check_extension(const char *filename)
{
	size_t len;

	if (!filename)
		return (0);
	len = ft_strlen((char *)filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}
