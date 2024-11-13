/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:27:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/13 12:10:49 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_right(data);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_left(data);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_down(data);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_up(data);
}

void	move_right(t_data *data)
{
	if (data->map[data->player_y][data->player_x + 1] != '1')
	{
		data->sprites->player->instances->x += 32;
		data->player_x++;
	}
}

void	move_left(t_data *data)
{
	if (data->map[data->player_y][data->player_x - 1] != '1')
	{
		data->sprites->player->instances->x -= 32;
		data->player_x--;
	}
}

void	move_down(t_data *data)
{
	if (data->map[data->player_y + 1][data->player_x] != '1')
	{
		data->sprites->player->instances->y += 32;
		data->player_y++;
	}
}

void	move_up(t_data *data)
{
	if (data->map[data->player_y - 1][data->player_x] != '1')
	{
		data->sprites->player->instances->y -= 32;
		data->player_y--;
	}
}
