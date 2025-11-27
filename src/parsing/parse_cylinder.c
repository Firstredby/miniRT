/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:47:28 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 10:57:53 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	add_cylinder(t_scene *scene)
{
	t_cylinder	*new_cylinder;
	t_cylinder	*current;

	new_cylinder = ft_calloc(sizeof(t_cylinder), 1);
	if (!new_cylinder)
		return (0);
	if (!scene->cylinder)
	{
		scene->cylinder = new_cylinder;
		return (1);
	}
	current = scene->cylinder;
	while (current->next)
		current = current->next;
	current->next = new_cylinder;
	return (1);
}

int	parse_cylinder(char *line, t_scene *scene, t_tracking *tracking)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (!add_cylinder(scene))
		return (free_array(split), print_error("Memory allocation failed"), 0);
	if (!parse_vec(split[1], &scene->cylinder->center)
		|| !parse_vec(split[2], &scene->cylinder->axis)
		|| !validate_normalized(scene->cylinder->axis, "Cylinder"))
		return (free_array(split), 0);
	if (!parse_double(split[3], &scene->cylinder->radius))
		return (free_array(split), 0);
	if (scene->cylinder->radius <= 0)
		return (print_error("Cylinder radius must be greater than 0"), \
			free_array(split), 0);
	if (!parse_double(split[4], &scene->cylinder->height))
		return (free_array(split), 0);
	if (scene->cylinder->height <= 0)
		return (print_error("Cylinder height must be greater than 0"), \
			free_array(split), 0);
	if (!parse_color(split[5], &scene->cylinder->color))
		return (free_array(split), 0);
	return (free_array(split), tracking->object_cout += 1, 1);
}
