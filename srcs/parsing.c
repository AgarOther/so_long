/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:16:59 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/08 23:03:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		{
			// Need to check once GNL is done, or leaks will happen.
			if (ft_strlen(tmp) != ft_strlen(map->str) || !ft_hasdigit(tmp))
			{
				free(tmp);
				ft_lstclear(&map);
				return (NULL);
			}
			ft_lstadd_back(&map, ft_lstnew(tmp));
		}
	}
	free(tmp);
	return (map);
}

static int	is_valid(t_map *head, char **tab, char *map, int i)
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
		if (!is_valid(head, map, map[i], i))
			return (NULL);
		lst_map = lst_map->next;
		i++;
	}
	map[i] = 0;
	ft_lstclear(&head);
	return (map);
}
