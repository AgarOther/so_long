/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:17 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/09 18:17:01 by scraeyme         ###   ########.fr       */
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
	if (!map || x < 0 || y < 0 || map[x][y] == '1' || map[x][y] == 'F')
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

static int	has_path_execute(char **map)
{
	t_parse	*items;
	int		x;
	int		y;
	int		path;

	items = malloc(sizeof(t_parse));
	if (!items)
		return (0);
	x = -1;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
		{
			if (map[x][y] == 'P')
				break ;
		}
		if (map[x][y] == 'P')
			break ;
	}
	items->collectibles = get_collectibles(map);
	items->exit = 1;
	flood_fill(map, x, y, items);
	path = (items->collectibles == 0 && items->exit == 0);
	free(items);
	ft_tabfree(map, ft_tablen((const char **)map));
	return (path);
}

int	has_path(char **map)
{
	char	**map_cpy;
	int		size;

	size = ft_tablen((const char **)map);
	map_cpy = ft_tabdup(map, size);
	if (!map_cpy)
	{
		ft_tabfree(map, size);
		return (0);
	}
	return (has_path_execute(map_cpy));
}
