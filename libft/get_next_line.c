/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:25:32 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/08/15 19:40:41 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_save(int fd, char *tmp, char *remainder)
{
	int		bytes_read;
	char	*buff;

	bytes_read = 1;
	if (!remainder)
		remainder = ft_strdup("");
	while (!ft_strchr(remainder, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(remainder);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		buff = remainder;
		remainder = ft_strjoin(buff, tmp);
		free(buff);
	}
	return (remainder);
}

static char	*extract_line(char *remainder)
{
	char	*line;
	int		i;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] != '\n' && remainder[i] != '\0')
		i++;
	line = ft_substr(remainder, 0, i + 1);
	return (line);
}

static char	*update_save(char *remainder)
{
	char	*tmp;
	int		i;
	int		remainder_len;

	i = 0;
	remainder_len = ft_strlen(remainder);
	while (remainder[i] != '\n' && remainder[i] != '\0')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	tmp = ft_substr(remainder, i + 1, remainder_len - i);
	free(remainder);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	remainder = read_and_save(fd, tmp, remainder);
	free(tmp);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	remainder = update_save(remainder);
	return (line);
}
