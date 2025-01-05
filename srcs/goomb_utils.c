/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goomb_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:32:32 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/06 00:45:24 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_instance_t	*find_goomb(t_data *data)
{
	int				x;
	int				y;
	size_t			i;
	mlx_instance_t	*goomb;
	
	x = data->player_x;
	y = data->player_y;
	i = 0;
	while (i < data->sprites->goomb->count)
	{
		goomb = &data->sprites->goomb->instances[i];
		if ((goomb->x == x * 32 && goomb->y == (y + 1) * 32)
			|| (goomb->x == x * 32 && goomb->y == (y - 1) * 32)
			|| (goomb->x == (x + 1) * 32 && goomb->y == y * 32)
			|| (goomb->x == (x - 1) * 32 && goomb->y == y * 32))
			return (goomb);
		i++;
	}
	return (NULL);
}

static unsigned long long	get_seed(char **map)
{
	int					i;
	int					j;
	unsigned long long	seed;

	i = 0;
	seed = 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			seed += map[i][j];
			if (map[i][j] == 'P')
				seed *= 512;
			j++;
		}
		i++;
	}
	return (seed);
}

char	**populate_goomb(char **map)
{
	int					i;
	int					j;
	unsigned long long	seed;

	i = 0;
	seed = get_seed(map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (seed % 10 == 0 && map[i][j] == '0')
				map[i][j] = 'G';
			j++;
			seed += (seed / 16) + 1;
		}
		i++;
	}
	return (map);
}
