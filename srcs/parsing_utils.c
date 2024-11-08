/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:17 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/08 16:38:33 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_ber_file(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 3)
		return (0);
	return (ft_strncmp(&str[i - 3], ".ber", 4) == 0);
}
