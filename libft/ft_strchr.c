/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:38:09 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/07/28 13:58:07 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c_char;

	i = 0;
	c_char = c;
	while (s[i] != '\0')
	{
		if (s[i] == c_char)
			return ((char *)&s[i]);
		i++;
	}
	if (c_char == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
