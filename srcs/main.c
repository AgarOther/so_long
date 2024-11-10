/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:17:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/10 16:26:26 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**print_error(int code)
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

static int	return_free(char **map)
{
	ft_tabfree(map, ft_tablen((const char **)map));
	ft_putendl_fd("Error\nCouldn't initialize MLX.", 1);
	return (1);
}

static int	set_data(t_data **data, char **map)
{
	(*data)->map = map;
	(*data)->w_width = ft_strlen((const char *)*map) * WIDTH;
	(*data)->w_height = ft_tablen((const char **)map) * HEIGHT;
	(*data)->mlx = mlx_init((*data)->w_width,
			(*data)->w_height, "so_long", true);
	if (!(*data)->mlx)
		return (0);
	if (!(*data)->w_width || !(*data)->w_height)
		return (0);
	(*data)->img = mlx_new_image((*data)->mlx, (*data)->w_width,
			(*data)->w_height);
	if (!(*data)->img)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	char		**map;
	t_data		*data;

	map = parse_map(argc, argv);
	if (!map)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data || !set_data(&data, map))
		return (return_free(map));
	if (mlx_image_to_window(data->mlx, data->img,
			data->w_width / 2, data->w_height / 2) < 0)
		return (return_free(map));
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	ft_tabfree(map, ft_tablen((const char **)map));
	free(data);
	mlx_terminate(data->mlx);
	return (0);
}
