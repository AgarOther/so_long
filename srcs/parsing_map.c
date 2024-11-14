/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:36:20 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/14 12:52:42 by scraeyme         ###   ########.fr       */
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

void	set_exit(t_data **data)
{
	int		x;
	int		y;
	char	**map;

	y = -1;
	map = (*data)->map;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'E')
				break ;
		}
		if (map[y][x] == 'E')
			break ;
	}
	(*data)->exit_x = x;
	(*data)->exit_y = y;
}
