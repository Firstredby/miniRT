/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:02:05 by aorth             #+#    #+#             */
/*   Updated: 2025/11/26 11:24:53 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	add_light(t_scene *scene)
{
	t_light	*new_light;
	t_light	*current;

	new_light = ft_calloc(sizeof(t_light), 1);
	if (!new_light)
		return (0);
	if (!scene->light)
	{
		scene->light = new_light;
		return (1);
	}
	current = scene->light;
	while (current->next)
		current = current->next;
	current->next = new_light;
	return (1);
}

int	parse_light(char *line, t_scene *scene, t_tracking *tracking)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (print_error("Memory allocation failed"), 0);
	if (!add_light(scene))
		return (free_array(split), \
			print_error("Memory allocation failed"), 0);
	if (!parse_vec(split[1], &scene->light->pos))
		return (free_array(split), 0);
	if (!parse_double(split[2], &scene->light->brightness))
		return (free_array(split), 0);
	if (scene->light->brightness < 0 || scene->light->brightness > 1)
		return (print_error("Light brightness must be in range [0.0, 1.0]"), \
			free_array(split), 0);
	if (!parse_color(split[3], &scene->light->color))
		return (free_array(split), 0);
	tracking->light_count += 1;
	free_array(split);
	return (1);
}
