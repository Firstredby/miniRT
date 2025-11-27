/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:50:20 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/27 15:15:45 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/miniRT.h"

int	sphere_loop(t_vec L, t_vec orig,
			double light_dist, t_scene *scene)
{
	t_hit		hit;
	t_sphere	*sphere;

	sphere = scene->sphere;
	while (sphere)
	{
		if (hit_sphere(orig, L, *sphere, &hit))
		{
			if (hit.t > 0 && hit.t < light_dist)
				return (1);
		}
		sphere = sphere->next;
	}
	return (0);
}

int	cylinder_loop(t_vec L, t_vec orig,
			double light_dist, t_scene *scene)
{
	t_hit		hit;
	t_cylinder	*cylinder;

	cylinder = scene->cylinder;
	while (cylinder)
	{
		if (hit_cylinder(orig, L, *cylinder, &hit))
		{
			if (hit.t > 0 && hit.t < light_dist)
				return (1);
		}
		cylinder = cylinder->next;
	}
	return (0);
}

int	plane_loop(t_vec L, t_vec orig,
			double light_dist, t_scene *scene)
{
	t_hit	hit;
	t_plane	*plane;

	plane = scene->plane;
	while (plane)
	{
		if (hit_plane(orig, L, *plane, &hit))
		{
			if (hit.t > 0 && hit.t < light_dist)
				return (1);
		}
		plane = plane->next;
	}
	return (0);
}
