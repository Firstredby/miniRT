/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:37:00 by aorth             #+#    #+#             */
/*   Updated: 2025/11/26 17:47:02 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	validate_double_format(char *str)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == '.' && !has_dot)
			{
				has_dot = 1;
				i++;
				continue ;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_double(char *str, double *value)
{
	if (!validate_double_format(str))
		return (print_error("Invalid Input"), 0);
	*value = atof(str);
	return (1);
}

int	parse_color(char *str, t_color *color)
{
	char	**split;
	long	r;
	long	g;
	long	b;

	split = ft_split(str, ',');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (count_array(split) != 3)
		return (free_array(split), \
			print_error("Color must have exactly 3 values (R,G,B)"), 0);
	r = ft_atol(split[0]);
	if (r > 255 || r < 0)
		return (free_array(split), \
			print_error("Color values must be in range [0, 255]"), 0);
	g = ft_atol(split[1]);
	if (g > 255 || g < 0)
		return (free_array(split), \
			print_error("Color values must be in range [0, 255]"), 0);
	b = ft_atol(split[2]);
	if (b > 255 || b < 0)
		return (free_array(split), \
			print_error("Color values must be in range [0, 255]"), 0);
	color->r = r / 255.0;
	color->g = g / 255.0;
	color->b = b / 255.0;
	free_array(split);
	return (1);
}

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

int	parse_int(char *str, int *value)
{
	int	temp;

	temp = ft_atol(str);
	if (temp < 0 || temp > 180)
		return (print_error("Camera FOV must be in range [0, 180]"), 0);
	*value = temp;
	return (1);
}
