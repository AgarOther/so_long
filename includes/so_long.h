/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:13:17 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/13 12:10:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define WIDTH 32
# define HEIGHT 32
# include "../libft/libft.h"
# include "../libft/ft_printf/includes/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h> // open
# include <string.h> // strerror
# include <stdio.h> // perror

// Add a t_textures and a t_images to store my textures as png files.
// Delete t_textures when t_images are done.

typedef struct s_parse
{
	int	collectibles;
	int	exit;
}			t_parse;

typedef struct s_textures
{
	mlx_texture_t	*player;
	mlx_texture_t	*wall;
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit;
	mlx_texture_t	*empty;
}			t_textures;

typedef struct s_sprites
{
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*empty;
}			t_sprites;

typedef struct s_data
{
	mlx_t		*mlx;
	t_textures	*textures;
	t_sprites	*sprites;
	char		**map;
	int			w_width;
	int			w_height;
	int			player_x;
	int			player_y;
}			t_data;

// Memory
int	free_data(t_data *data);

// Textures
int		load_textures(t_data *data);

// Parsing
int		is_ber_file(char *str);
char	**get_map(int fd);
int		has_path(char **map, t_data *data);
int		has_correct_features(t_map *map);

// Player Movement
void	key_hook(mlx_key_data_t keydata, void *param);
void	move_right(t_data *data);
void	move_left(t_data *data);
void	move_down(t_data *data);
void	move_up(t_data *data);

#endif
