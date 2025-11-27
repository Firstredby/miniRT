/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:02:39 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 19:09:11 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static t_plane	*add_plane(t_scene *scene)
{
	t_plane	*new_plane;
	t_plane	*current;

	new_plane = ft_calloc(sizeof(t_plane), 1);
	if (!new_plane)
		return (NULL);
	if (!scene->plane)
	{
		scene->plane = new_plane;
		return (new_plane);
	}
	current = scene->plane;
	while (current->next)
		current = current->next;
	current->next = new_plane;
	return (new_plane);
}

int	parse_plane(char *line, t_scene *scene, t_tracking *tracking)
{
	char	**split;
	t_plane	*new_plane;

	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	new_plane = add_plane(scene);
	if (!new_plane)
		return (free_array(split),
			print_error("Memory allocation failed"), 0);
	if (!parse_vec(split[1], &new_plane->center))
		return (free_array(split), 0);
	if (!parse_vec(split[2], &new_plane->axis))
		return (free_array(split), 0);
	if (!validate_normalized(new_plane->axis, "Plane"))
		return (free_array(split), 0);
	if (!parse_color(split[3], &new_plane->color))
		return (free_array(split), 0);
	tracking->object_cout += 1;
	free_array(split);
	return (1);
}
