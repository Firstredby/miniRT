/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:25:43 by aorth             #+#    #+#             */
/*   Updated: 2025/11/25 12:13:43 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	free_spehere(t_sphere *sphere)
{
	t_sphere	*current;
	t_sphere	*next;

	current = sphere;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_plane(t_plane *plane)
{
	t_plane	*current;
	t_plane	*next;

	current = plane;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_cylinder(t_cylinder *cylinder)
{
	t_cylinder	*current;
	t_cylinder	*next;

	current = cylinder;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_light(t_light *light)
{
	t_light	*current;
	t_light	*next;

	current = light;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->sphere)
		free_spehere(scene->sphere);
	if (scene->plane)
		free_plane(scene->plane);
	if (scene->cylinder)
		free_cylinder(scene->cylinder);
	if (scene->light)
		free_light(scene->light);
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	free(scene);
}
