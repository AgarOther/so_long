/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:17:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/09 18:21:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_error(int code)
{
	if (code == 0)
		ft_printf("Error! Please specify a .ber file.\n");
	else if (code == 1)
		ft_printf("Error! File doesn't exist.\n");
	else if (code == 2)
		ft_printf("Error! Map is invalid.\n");
	else if (code == 3)
		ft_printf("Error! Path is invalid.\n");
	return (1);
}

int	main(int argc, char **argv)
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
	ft_tabprint(map, 0);
	ft_tabfree(map, ft_tablen((const char **)map));
	return (0);
}
