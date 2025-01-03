/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:27:43 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/03 17:44:20 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
