/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:13:17 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/14 13:41:11 by scraeyme         ###   ########.fr       */
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
# include <fcntl.h>

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
	int			exit_x;
	int			exit_y;
	int			steps;
	int			collectibles_left;
}			t_data;

// Memory
int		free_data(t_data *data, int textures);

// Textures
int		load_textures(t_data *data);
int		draw_texture(t_data	*data, char type, int x, int y);

// Parsing
int		is_ber_file(char *str);
char	**get_map(int fd, int i);
int		has_path(char **map, t_data **data);
int		has_correct_features(t_map *map);
void	set_exit(t_data **data);

// Player Movement
void	move_right(t_data *data);
void	move_left(t_data *data);
void	move_down(t_data *data);
void	move_up(t_data *data);

#endif
