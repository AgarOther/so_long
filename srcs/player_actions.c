/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:27:43 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/06 12:51:46 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hit_goomb(t_data *data)
{
	mlx_instance_t	*goomb;

	goomb = find_goomb(data);
	if (!goomb)
		return ;
	goomb->enabled = 0;
	data->map[goomb->y / 32][goomb->x / 32] = '0';
}

void	move_right(t_data *data)
{
	if (data->map[data->player_y][data->player_x + 1] != '1')
	{
		if (data->map[data->player_y][data->player_x + 1] == 'G')
		{
			ft_printf("Too bad! You hit a Goomb and died.\n");
			mlx_close_window(data->mlx);
			return ;
		}
		data->sprites->player->instances->x += 32;
		data->player_x++;
		add_step(data, 0);
	}
}

void	move_left(t_data *data)
{
	if (data->map[data->player_y][data->player_x - 1] != '1')
	{
		if (data->map[data->player_y][data->player_x - 1] == 'G')
		{
			ft_printf("Too bad! You hit a Goomb and died.\n");
			mlx_close_window(data->mlx);
			return ;
		}
		data->sprites->player->instances->x -= 32;
		data->player_x--;
		add_step(data, 0);
	}
}

void	move_down(t_data *data)
{
	if (data->map[data->player_y + 1][data->player_x] != '1')
	{
		if (data->map[data->player_y + 1][data->player_x] == 'G')
		{
			ft_printf("Too bad! You hit a Goomb and died.\n");
			mlx_close_window(data->mlx);
			return ;
		}
		data->sprites->player->instances->y += 32;
		data->player_y++;
		add_step(data, 0);
	}
}

void	move_up(t_data *data)
{
	if (data->map[data->player_y - 1][data->player_x] != '1')
	{
		if (data->map[data->player_y - 1][data->player_x] == 'G')
		{
			ft_printf("Too bad! You hit a Goomb and died.\n");
			mlx_close_window(data->mlx);
			return ;
		}
		data->sprites->player->instances->y -= 32;
		data->player_y--;
		add_step(data, 0);
	}
}
