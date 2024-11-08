/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:16:59 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/08 17:57:56 by scraeyme         ###   ########.fr       */
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
			ft_lstadd_back(&map, ft_lstnew(tmp));
	}
	return (map);
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
		lst_map = lst_map->next;
		i++;
	}
	map[i] = 0;
	ft_lstclear(&head);
	return (map);
}
