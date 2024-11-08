/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:17:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/08 22:30:52 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_tabprint(map, 0);
	ft_tabfree(map, ft_tablen((const char **)map));
	return (0);
}
