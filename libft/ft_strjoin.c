/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:35:27 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/07/29 18:49:03 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1i;
	size_t	s2i;
	char	*sc;

	s1i = 0;
	s2i = 0;
	if (!s1 || !s2)
		return (NULL);
	sc = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!sc)
		return (NULL);
	while (s1[s1i] != '\0')
	{
		sc[s1i] = s1[s1i];
		s1i++;
	}
	while (s2[s2i] != '\0')
	{
		sc[s1i + s2i] = s2[s2i];
		s2i++;
	}
	sc[s1i + s2i] = '\0';
	return (sc);
}
