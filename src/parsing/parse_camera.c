/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:42:34 by aorth             #+#    #+#             */
/*   Updated: 2025/11/25 12:09:09 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parse_camera(char *line, t_scene *scene, t_tracking *tracking)
{
	char	**split;

	if (tracking->has_camera)
		return (print_error("Duplicate camera definition"), 0);
	scene->camera = ft_calloc(sizeof(t_camera), 1);
	if (!scene->camera)
		return (print_error("Memory allocation failed"), 0);
	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (count_array(split) < 4)
		return (free_array(split), \
			print_error("Camera: missing parameters"), 0);
	if (!parse_vec(split[1], &scene->camera->pos))
		return (free_array(split), 0);
	if (!parse_vec(split[2], &scene->camera->orientation))
		return (free_array(split), 0);
	if (!validate_normalized(scene->camera->orientation, "Camera"))
		return (free_array(split), 0);
	if (!parse_int(split[3], &scene->camera->fov))
		return (free_array(split), 0);
	tracking->has_camera = 1;
	free_array(split);
	return (1);
	
}
