/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:30:00 by aorth             #+#    #+#             */
/*   Updated: 2025/11/25 12:23:28 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	init_tracking(t_tracking *tracking)
{
	tracking->filename = NULL;
	tracking->has_ambient = 0;
	tracking->has_camera = 0;
	tracking->light_count = 0;
	tracking->line_number = 0;
	tracking->object_cout = 0;
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = ft_calloc(sizeof(t_scene), 1);
	if (!scene)
		return (print_error("Memory allocation failed"), NULL);
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->cylinder = NULL;
	scene->light = NULL;
	scene->plane = NULL;
	scene->sphere = NULL;
	return (scene);
}
