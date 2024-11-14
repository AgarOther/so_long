/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:28:02 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/14 13:42:05 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_image(mlx_t *mlx, mlx_image_t *sprite)
{
	if (sprite)
		mlx_delete_image(mlx, sprite);
}

static void	free_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	free_textures(t_data *data)
{
	free_texture(data->textures->player);
	free_texture(data->textures->wall);
	free_texture(data->textures->collectible);
	free_texture(data->textures->exit);
	free_texture(data->textures->empty);
	free(data->textures);
	free_image(data->mlx, data->sprites->player);
	free_image(data->mlx, data->sprites->wall);
	free_image(data->mlx, data->sprites->collectible);
	free_image(data->mlx, data->sprites->exit);
	free_image(data->mlx, data->sprites->empty);
	free(data->sprites);
}

int	free_data(t_data *data, int textures)
{
	if (textures)
		free_textures(data);
	mlx_terminate(data->mlx);
	ft_tabfree(data->map, ft_tablen((const char **)data->map));
	free(data);
	return (0);
}
