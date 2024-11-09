/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:16:59 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/09 21:23:36 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	has_all_features(t_map *map)
{
	int		player;
	int		collectibles;
	int		exit;
	int		i;
	char	*tmp;

	player = 0;
	collectibles = 0;
	exit = 0;
	while (map)
	{
		i = -1;
		tmp = map->str;
		while (tmp[++i])
		{
			if (tmp[i] == 'C' && !collectibles)
				collectibles = 1;
			else if (tmp[i] == 'E' && !exit)
				exit = 1;
			else if (tmp[i] == 'P' && !player)
				player = 1;
		}
		map = map->next;
	}
	return (player + collectibles + exit == 3);
}

static int	is_map_valid(t_map *map)
{
	t_map	*head;
	char	*tmp;
	size_t	size;
	int		i;

	head = map;
	size = ft_strlen(map->str);
	map = map->next;
	while (map)
	{
		i = -1;
		tmp = map->str;
		while (tmp[++i])
		{
			if (tmp[i] != '0' && tmp[i] != '1' && tmp[i] != 'C'
				&& tmp[i] != 'E' && tmp[i] != 'P' && tmp[i] != '\n')
				return (0);
		}
		if (ft_strlen(tmp) + (tmp[i - 1] != '\n') != size)
			return (0);
		map = map->next;
	}
	if (!has_correct_features(head))
		return (0);
	return (1);
}

static t_map	*get_map_as_list(int fd)
{
	char	*tmp;
	t_map	*map;

	map = NULL;
	while (!map || tmp)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (!map)
			map = ft_lstnew(tmp);
		else
			ft_lstadd_back(&map, ft_lstnew(tmp));
	}
	free(tmp);
	if (!map || !is_map_valid(map) || !has_all_features(map))
	{
		ft_lstclear(&map);
		return (NULL);
	}
	return (map);
}

static int	has_walls(t_map *head, char **tab, char *map, int i)
{
	int	size;

	size = ft_lstsize(head);
	if (((i == 0 || i == size - 1) && !ft_isfilled(map, '1', "\n"))
		|| (i > 0 && i < size - 1 && !ft_istrimmable(map, '1'))
		|| size <= 2)
	{
		ft_tabfree(tab, i + 1);
		ft_lstclear(&head);
		return (0);
	}
	return (1);
}

char	**get_map(int fd)
{
	t_map	*head;
	t_map	*lst_map;
	char	**map;
	int		i;

	lst_map = get_map_as_list(fd);
	head = lst_map;
	if (!lst_map)
		return (NULL);
	map = malloc((ft_lstsize(lst_map) + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (lst_map)
	{
		map[i] = ft_strdup(lst_map->str);
		if (!has_walls(head, map, map[i], i))
			return (NULL);
		lst_map = lst_map->next;
		i++;
	}
	map[i] = 0;
	ft_lstclear(&head);
	return (map);
}
