/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:17 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/14 13:37:17 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_ber_file(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 3)
		return (0);
	return (ft_strncmp(&str[i - 3], ".ber", 4) == 0);
}

static int	get_collectibles(char **map)
{
	int	x;
	int	y;
	int	collectibles;

	x = 0;
	collectibles = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'C')
				collectibles++;
			y++;
		}
		x++;
	}
	return (collectibles);
}

static void	flood_fill(char **map, int x, int y, t_parse *items)
{
	if (!map || x < 0 || y < 0 || map[x][y] == '1' || map[x][y] == 'F'
		|| x > 100 || y > 100)
		return ;
	if (map[x][y] == 'C')
		items->collectibles--;
	else if (map[x][y] == 'E')
		items->exit--;
	map[x][y] = 'F';
	flood_fill(map, x, y + 1, items);
	flood_fill(map, x, y - 1, items);
	flood_fill(map, x + 1, y, items);
	flood_fill(map, x - 1, y, items);
}

static int	has_path_execute(char **map, t_parse *items, t_data *data)
{
	int		x;
	int		y;
	int		path;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
				break ;
		}
		if (map[y][x] == 'P')
			break ;
	}
	flood_fill(map, y, x, items);
	path = (items->collectibles == 0 && items->exit == 0);
	free(items);
	ft_tabfree(map, ft_tablen((const char **)map));
	data->player_x = x;
	data->player_y = y;
	return (path);
}

int	has_path(char **map, t_data **data)
{
	t_parse	*items;
	char	**map_cpy;
	int		size;

	items = malloc(sizeof(t_parse));
	if (!items)
		return (0);
	size = ft_tablen((const char **)map);
	map_cpy = ft_tabdup(map, size);
	if (!map_cpy)
	{
		free(items);
		return (0);
	}
	items->collectibles = get_collectibles(map);
	(*data)->collectibles_left = items->collectibles;
	items->exit = 1;
	return (has_path_execute(map_cpy, items, *data));
}
