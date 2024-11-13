/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:17:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/13 12:11:08 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**print_error(int code, t_data *data)
{
	ft_putendl_fd("Error", 1);
	if (code == 0)
		ft_putendl_fd("Please specify a .ber file.", 1);
	else if (code == 1)
		ft_putendl_fd("File doesn't exist.", 1);
	else if (code == 2)
		ft_putendl_fd("Map is invalid.", 1);
	else if (code == 3)
		ft_putendl_fd("Path is invalid.", 1);
	else if (code == 4)
		ft_putendl_fd("Error\nCouldn't initialize MLX.", 1);
	free(data);
	return (NULL);
}

static char	**parse_map(int argc, char **argv, t_data *data)
{
	int		fd;
	char	**map;

	if (argc != 2 || !is_ber_file(argv[1]))
		return (print_error(0, data));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (print_error(1, data));
	map = get_map(fd);
	if (!map)
		return (print_error(2, data));
	close(fd);
	if (!has_path(map, data))
	{
		ft_tabfree(map, ft_tablen((const char **)map));
		return (print_error(3, data));
	}
	return (map);
}

static int	set_data(t_data **data, char **map)
{
	(*data)->map = map;
	(*data)->w_width = (ft_strlen((const char *)*map) - 1) * WIDTH;
	(*data)->w_height = ft_tablen((const char **)map) * HEIGHT;
	(*data)->mlx = mlx_init((*data)->w_width,
			(*data)->w_height, "so_long", true);
	if (!(*data)->mlx)
		return (0);
	if (!(*data)->w_width || !(*data)->w_height)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	char			**map;
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	map = parse_map(argc, argv, data);
	if (!map)
		return (1);
	if (!set_data(&data, map) || !load_textures(data))
	{
		ft_putendl_fd("Error\nCouldn't initialize MLX. "
			"Check if your textures are correct.", 1);
		return (free_data(data));
	}
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_loop(data->mlx);
	free_data(data);
	return (0);
}
