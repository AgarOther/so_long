/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:07:52 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/05 23:26:50 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate(void *param)
{
	t_data		*data;
	int			i;
	int			instances;
	static int	frames = -1;	
	static int	way = 1;

	data = (t_data *) param;
	frames++;
	if (frames >= FRAME_TIME)
	{
		i = 0;
		instances = data->sprites->collectible->count;
		while (i < instances)
		{
			if (way && data->sprites->collectible->instances[i].enabled)
				data->sprites->collectible->instances[i].y--;
			else if (!way && data->sprites->collectible->instances[i].enabled)
				data->sprites->collectible->instances[i].y++;
			i++;
		}
		way = 1 - way;
		frames = 0;
	}
}

static void	look_for_sprite(t_data *data, int i)
{
	if (data->sprites->collectible->instances[i].x
		== data->player_x * 32
		&& data->sprites->collectible->instances[i].y
		== data->player_y * 32)
		data->sprites->collectible->instances[i].enabled = 0;
	else if (data->sprites->collectible->instances[i].x
		== data->player_x * 32
		&& data->sprites->collectible->instances[i].y + 1
		== data->player_y * 32)
		data->sprites->collectible->instances[i].enabled = 0;
	else if (data->sprites->collectible->instances[i].x
		== data->player_x * 32
		&& data->sprites->collectible->instances[i].y - 1
		== data->player_y * 32)
		data->sprites->collectible->instances[i].enabled = 0;
}

void	add_step(t_data *data, size_t i)
{
	data->steps++;
	print_steps(data);
	if (data->map[data->player_y][data->player_x] == 'C')
	{
		data->collectibles_left--;
		data->map[data->player_y][data->player_x] = '0';
		while (i < data->sprites->collectible->count)
		{
			look_for_sprite(data, i);
			i++;
		}
		if (data->collectibles_left == 0)
			mlx_image_to_window(data->mlx, data->sprites->exit,
				data->exit_x * 32, data->exit_y * 32);
	}
	else if (data->map[data->player_y][data->player_x] == 'E'
		&& data->collectibles_left == 0)
	{
		ft_printf("Good job! You finished in %d moves.\n", data->steps);
		mlx_close_window(data->mlx);
	}
}
