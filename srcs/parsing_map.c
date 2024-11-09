/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:36:20 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/09 16:41:25 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_correct_features(t_map *map)
{
	int		exit;
	int		player;
	char	*tmp;

	exit = 0;
	player = 0;
	while (map)
	{
		tmp = map->str;
		exit += ft_stroccur(tmp, 'E');
		player += ft_stroccur(tmp, 'P');
		map = map->next;
	}
	return (exit == 1 && player == 1);
}
