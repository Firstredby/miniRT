/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:37:00 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 10:46:19 by aorth            ###   ########.fr       */
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
	*value = ft_atof(str);
	return (1);
}

static int	validate_color_value(long val, char **split)
{
	if (val < 0 || val > 255)
		return (free_array(split), \
			print_error("Color values must be in range [0, 255]"), 0);
	return (1);
}

int	parse_color(char *str, t_color *color)
{
	char	**split;
	long	rgb[3];

	split = ft_split(str, ',');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (count_array(split) != 3)
		return (free_array(split), \
			print_error("Color must have exactly 3 values (R,G,B)"), 0);
	rgb[0] = ft_atol(split[0]);
	rgb[1] = ft_atol(split[1]);
	rgb[2] = ft_atol(split[2]);
	if (!validate_color_value(rgb[0], split)
		|| !validate_color_value(rgb[1], split)
		|| !validate_color_value(rgb[2], split))
		return (0);
	color->r = rgb[0] / 255.0;
	color->g = rgb[1] / 255.0;
	color->b = rgb[2] / 255.0;
	return (free_array(split), 1);
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
