/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:46:03 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 10:46:26 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parse_vec(char *str, t_vec *vec)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (count_array(split) != 3)
		return (free_array(split), \
			print_error("Vector must have exactly 3 values (x,y,z)"), 0);
	if (!parse_double(split[0], &vec->x))
		return (free_array(split), 0);
	if (!parse_double(split[1], &vec->y))
		return (free_array(split), 0);
	if (!parse_double(split[2], &vec->z))
		return (free_array(split), 0);
	free_array(split);
	return (1);
}
