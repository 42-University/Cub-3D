/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:29:57 by tkenji-u          #+#    #+#             */
/*   Updated: 2026/05/04 20:30:20 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
