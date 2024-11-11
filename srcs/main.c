/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:17:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/10 22:28:59 by scraeyme         ###   ########.fr       */
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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->player->instances->x += 32;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->player->instances->x -= 32;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		data->player->instances->y -= 32;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		data->player->instances->y += 32;
}

int	main(int argc, char **argv)
{
	char			**map;
	t_data			*data;
	mlx_texture_t	*texture;
	mlx_image_t		*displayable_image;

	map = parse_map(argc, argv);
	if (!map)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data || !set_data(&data, map))
		return (return_free(map));
	if (mlx_image_to_window(data->mlx, data->img,
			data->w_width / 2, data->w_height / 2) < 0)
		return (return_free(map));
	texture = mlx_load_png("owo.png");
	if (!texture)
	{
		ft_printf("nope\n");
		return (0);
	}
	displayable_image = mlx_texture_to_image(data->mlx, texture);
	mlx_image_to_window(data->mlx, displayable_image, 0, 0);
	data->player = displayable_image;
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	ft_tabfree(map, ft_tablen((const char **)map));
	mlx_terminate(data->mlx);
	free(data);
	return (0);
}
