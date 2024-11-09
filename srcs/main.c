/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:17:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/09 21:54:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**print_error(int code)
{
	ft_putendl_fd("Error", 2);
	if (code == 0)
		ft_putendl_fd("Please specify a .ber file.", 2);
	else if (code == 1)
		ft_putendl_fd("File doesn't exist.", 2);
	else if (code == 2)
		ft_putendl_fd("Map is invalid.", 2);
	else if (code == 3)
		ft_putendl_fd("Path is invalid.", 2);
	return (NULL);
}

static char	**parse_map(int argc, char **argv)
{
	int		fd;
	char	**map;

	if (argc != 2 || !is_ber_file(argv[1]))
		return (print_error(0));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (print_error(1));
	map = get_map(fd);
	if (!map)
		return (print_error(2));
	close(fd);
	if (!has_path(map))
	{
		ft_tabfree(map, ft_tablen((const char **)map));
		return (print_error(3));
	}
	return (map);
}

int	main(int argc, char **argv)
{
	char	**map;

	map = parse_map(argc, argv);
	if (!map)
		return (0);
	ft_tabprint(map, 0);
	ft_tabfree(map, ft_tablen((const char **)map));
	return (0);
}
