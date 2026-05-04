/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:34:38 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/07/29 19:01:07 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c);
static void		skip_delim(const char **s, char c);
static void		free_split(char **arr, size_t i);
static char		*get_word(const char *s, char c);

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	skip_delim(const char **s, char c)
{
	while (**s && **s == c)
		(*s)++;
}

static void	free_split(char **arr, size_t i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
}

static char	*get_word(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (ft_substr(s, 0, len));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words)
	{
		skip_delim(&s, c);
		arr[i] = get_word(s, c);
		if (!arr[i])
		{
			free_split(arr, i);
			return (NULL);
		}
		s += ft_strlen(arr[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
