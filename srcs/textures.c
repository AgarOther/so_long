/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:50:24 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/03 18:12:26 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_steps(t_data *data)
{
	char				*steps;
	static mlx_image_t	*steps_str = NULL;

	steps = ft_itoa(data->steps);
	if (steps_str)
		mlx_delete_image(data->mlx, steps_str);
	steps_str = mlx_put_string(data->mlx, steps, 5, 5);
	free(steps);
}

static t_textures	*get_textures(void)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->player = mlx_load_png("./textures/player.png");
	textures->wall = mlx_load_png("./textures/wall.png");
	textures->collectible = mlx_load_png("./textures/collectible.png");
	textures->exit = mlx_load_png("./textures/exit.png");
	textures->empty = mlx_load_png("./textures/empty.png");
	textures->goomb = mlx_load_png("./textures/goomb.png");
	if (!textures->player || !textures->wall || !textures->collectible
		|| !textures->exit || !textures->empty || !textures->goomb)
		return (NULL);
	return (textures);
}

static int	set_textures(t_data **data)
{
	t_sprites	*sprites;
	t_textures	*textures;

	sprites = malloc(sizeof(t_sprites));
	if (!sprites)
		return (0);
	textures = get_textures();
	if (!textures)
		return (0);
	sprites->player = mlx_texture_to_image((*data)->mlx, textures->player);
	sprites->wall = mlx_texture_to_image((*data)->mlx, textures->wall);
	sprites->collectible = mlx_texture_to_image((*data)->mlx,
			textures->collectible);
	sprites->exit = mlx_texture_to_image((*data)->mlx, textures->exit);
	sprites->empty = mlx_texture_to_image((*data)->mlx, textures->empty);
	sprites->goomb = mlx_texture_to_image((*data)->mlx, textures->goomb);
	(*data)->sprites = sprites;
	(*data)->textures = textures;
	return (1);
}

int	draw_texture(t_data	*data, char type, int x, int y)
{
	mlx_image_t	*tmp;

	if (type == '1')
		tmp = data->sprites->wall;
	else if (type == 'C')
	{
		tmp = data->sprites->empty;
		if (mlx_image_to_window(data->mlx, tmp, x * 32, y * 32) == -1)
			return (0);
		tmp = data->sprites->collectible;
	}
	else if (type == '0' || type == 'P' || type == 'E')
		tmp = data->sprites->empty;
	else
		return (-1);
	if (mlx_image_to_window(data->mlx, tmp, x * 32, y * 32) == -1)
		return (0);
	return (1);
}

int	load_textures(t_data *data)
{
	int	x;
	int	y;

	if (!set_textures(&data))
		return (0);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!draw_texture(data, data->map[y][x], x, y))
				return (0);
			x++;
		}
		y++;
	}
	if (mlx_image_to_window(data->mlx, data->sprites->player,
			data->player_x * 32, data->player_y * 32) == -1)
		return (0);
	return (1);
}
