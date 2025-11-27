/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:02:29 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 19:11:32 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static t_sphere	*add_speher(t_scene *scene)
{
	t_sphere	*new_sphere;
	t_sphere	*current;

	new_sphere = ft_calloc(sizeof(t_sphere), 1);
	if (!new_sphere)
		return (NULL);
	if (!scene->sphere)
	{
		scene->sphere = new_sphere;
		return (new_sphere);
	}
	current = scene->sphere;
	while (current->next)
		current = current->next;
	current->next = new_sphere;
	return (new_sphere);
}

int	parse_sphere(char *line, t_scene *scene, t_tracking *tracking)
{
	char		**split;
	t_sphere	*new_sphere;

	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	new_sphere = add_speher(scene);
	if (!new_sphere)
		return (free_array(split),
			print_error("Memory allocation failed"), 0);
	if (!parse_vec(split[1], &new_sphere->center))
		return (free_array(split), 0);
	if (!parse_double(split[2], &new_sphere->radius))
		return (free_array(split), 0);
	if (new_sphere->radius <= 0)
		return (print_error("Sphere radius must be greater than 0"),
			free_array(split), 0);
	if (!parse_color(split[3], &new_sphere->color))
		return (free_array(split), 0);
	tracking->object_cout += 1;
	free_array(split);
	return (1);
}
