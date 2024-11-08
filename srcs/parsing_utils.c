/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:17 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/08 22:25:15 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_error(int code)
{
	if (code == 0)
		ft_printf("Error! Please specify a .ber file.\n");
	else if (code == 1)
		ft_printf("Error! File doesn't exist.\n");
	else if (code == 2)
		ft_printf("Error! Map is invalid.\n");
	return (1);
}

int	is_ber_file(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 3)
		return (0);
	return (ft_strncmp(&str[i - 3], ".ber", 4) == 0);
}
