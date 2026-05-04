/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:12:26 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/07/30 10:31:52 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	mem = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		mem[i] = (unsigned char)c;
		i++;
	}
	return (mem);
}
