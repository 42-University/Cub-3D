/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 20:00:00 by liferrei          #+#    #+#             */
/*   Updated: 2026/05/04 20:00:00 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_hook	hook_game(int (*f)(t_game *))
{
	t_game_hook	h;

	h.typed = f;
	return (h.generic);
}

t_hook	hook_key(int (*f)(int, t_game *))
{
	t_key_hook	h;

	h.typed = f;
	return (h.generic);
}
