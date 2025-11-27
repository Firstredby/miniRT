/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:10:09 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 19:10:07 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parse_ambient(char *line, t_scene *scene, t_tracking *tracking)
{
	char	**split;

	if (tracking->has_ambient)
		return (print_error("Duplicate ambient light definition"), 0);
	scene->ambient = ft_calloc(sizeof(t_ambient), 1);
	if (!scene->ambient)
		return (print_error("Memory allocation failed"), 0);
	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (!parse_double(split[1], &scene->ambient->ratio))
		return (free_array(split), 0);
	if (!parse_color(split[2], &scene->ambient->color))
		return (free_array(split), 0);
	if (scene->ambient->ratio > 1 || scene->ambient->ratio < 0)
		return (free_array(split),
			print_error("Ambient ratio must be in range [0.0, 1.0]"), 0);
	tracking->has_ambient = 1;
	free_array(split);
	return (1);
}
