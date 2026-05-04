/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:25:29 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/08/14 14:31:16 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		s++;
		length++;
	}
	return (length);
}

char	*ft_strdup(const char *s)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = (unsigned char *)malloc(i + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return ((char *)ptr);
}

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	subs_len;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		subs_len = 0;
	else if (len > s_len - start)
		subs_len = s_len - start;
	else
		subs_len = len;
	subs = malloc(subs_len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < subs_len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[subs_len] = '\0';
	return (subs);
}
