/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:39:35 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/07/24 16:12:02 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
