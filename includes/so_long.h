/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:13:17 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/10 16:16:30 by scraeyme         ###   ########.fr       */
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

typedef struct s_parse
{
	int	collectibles;
	int	exit;
}			t_parse;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		**map;
	int			w_width;
	int			w_height;
}			t_data;

//Parsing
int		is_ber_file(char *str);
char	**get_map(int fd);
int		has_path(char **map);
int		has_correct_features(t_map *map);

#endif
