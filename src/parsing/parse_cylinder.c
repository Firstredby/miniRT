/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:47:28 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 19:11:05 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static t_cylinder	*add_cylinder(t_scene *scene)
{
	t_cylinder	*new_cylinder;
	t_cylinder	*current;

	new_cylinder = ft_calloc(sizeof(t_cylinder), 1);
	if (!new_cylinder)
		return (NULL);
	if (!scene->cylinder)
	{
		scene->cylinder = new_cylinder;
		return (new_cylinder);
	}
	current = scene->cylinder;
	while (current->next)
		current = current->next;
	current->next = new_cylinder;
	return (new_cylinder);
}

int	parse_cylinder(char *line, t_scene *scene, t_tracking *tracking)
{
	char		**split;
	t_cylinder	*new_cylinder;

	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	new_cylinder = add_cylinder(scene);
	if (!new_cylinder)
		return (free_array(split), print_error("Memory allocation failed"), 0);
	if (!parse_vec(split[1], &new_cylinder->center)
		|| !parse_vec(split[2], &new_cylinder->axis)
		|| !validate_normalized(new_cylinder->axis, "Cylinder"))
		return (free_array(split), 0);
	if (!parse_double(split[3], &new_cylinder->radius)
		|| !parse_double(split[4], &new_cylinder->height))
		return (free_array(split), 0);
	if (new_cylinder->radius <= 0)
		return (print_error("Cylinder radius must be greater than 0"),
			free_array(split), 0);
	if (new_cylinder->height <= 0)
		return (print_error("Cylinder height must be greater than 0"),
			free_array(split), 0);
	if (!parse_color(split[5], &new_cylinder->color))
		return (free_array(split), 0);
	return (free_array(split), tracking->object_cout += 1, 1);
}
