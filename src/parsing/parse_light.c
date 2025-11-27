/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:02:05 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 19:06:46 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static t_light	*add_light(t_scene *scene)
{
	t_light	*new_light;
	t_light	*current;

	new_light = ft_calloc(sizeof(t_light), 1);
	if (!new_light)
		return (NULL);
	if (!scene->light)
	{
		scene->light = new_light;
		return (new_light);
	}
	current = scene->light;
	while (current->next)
		current = current->next;
	current->next = new_light;
	return (new_light);
}

int	parse_light(char *line, t_scene *scene, t_tracking *tracking)
{
	char	**split;
	t_light	*new_light;

	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	new_light = add_light(scene);
	if (!new_light)
		return (free_array(split),
			print_error("Memory allocation failed"), 0);
	if (!parse_vec(split[1], &new_light->pos))
		return (free_array(split), 0);
	if (!parse_double(split[2], &new_light->brightness))
		return (free_array(split), 0);
	if (new_light->brightness < 0 || new_light->brightness > 1)
		return (print_error("Light brightness must be in range [0.0, 1.0]"),
			free_array(split), 0);
	if (!parse_color(split[3], &new_light->color))
		return (free_array(split), 0);
	tracking->light_count += 1;
	free_array(split);
	return (1);
}
