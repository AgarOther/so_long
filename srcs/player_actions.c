/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:27:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/14 13:27:24 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_step(t_data *data, size_t i)
{
	data->steps++;
	ft_printf("Steps: %d\n", data->steps);
	if (data->map[data->player_y][data->player_x] == 'C')
	{
		data->collectibles_left--;
		data->map[data->player_y][data->player_x] = '0';
		while (i < data->sprites->collectible->count)
		{
			if (data->sprites->collectible->instances[i].x
				== data->player_x * 32
				&& data->sprites->collectible->instances[i].y
				== data->player_y * 32)
				data->sprites->collectible->instances[i].enabled = 0;
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

void	move_right(t_data *data)
{
	if (data->map[data->player_y][data->player_x + 1] != '1')
	{
		data->sprites->player->instances->x += 32;
		data->player_x++;
		add_step(data, 0);
	}
}

void	move_left(t_data *data)
{
	if (data->map[data->player_y][data->player_x - 1] != '1')
	{
		data->sprites->player->instances->x -= 32;
		data->player_x--;
		add_step(data, 0);
	}
}

void	move_down(t_data *data)
{
	if (data->map[data->player_y + 1][data->player_x] != '1')
	{
		data->sprites->player->instances->y += 32;
		data->player_y++;
		add_step(data, 0);
	}
}

void	move_up(t_data *data)
{
	if (data->map[data->player_y - 1][data->player_x] != '1')
	{
		data->sprites->player->instances->y -= 32;
		data->player_y--;
		add_step(data, 0);
	}
}
