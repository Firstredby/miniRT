/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:02:39 by aorth             #+#    #+#             */
/*   Updated: 2025/11/26 11:25:44 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	add_plane(t_scene *scene)
{
	t_plane	*new_plane;
	t_plane	*current;

	new_plane = ft_calloc(sizeof(t_plane), 1);
	if (!new_plane)
		return (0);
	if (!scene->plane)
	{
		scene->plane = new_plane;
		return (1);
	}
	current = scene->plane;
	while (current->next)
		current = current->next;
	current->next = new_plane;
	return (1);
}

int	parse_plane(char *line, t_scene *scene, t_tracking *tracking)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (!add_plane(scene))
		return (free_array(split), \
			print_error("Memory allocation failed"), 0);
	if (!parse_vec(split[1], &scene->plane->center))
		return (free_array(split), 0);
	if (!parse_vec(split[2], &scene->plane->axis))
		return (free_array(split), 0);
	if (!validate_normalized(scene->plane->axis, "Plane"))
		return (free_array(split), 0);
	if (!parse_color(split[3], &scene->plane->color))
		return (free_array(split), 0);
	tracking->object_cout += 1;
	free_array(split);
	return (1);
}