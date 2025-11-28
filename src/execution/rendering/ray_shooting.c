/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shooting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:35:32 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/28 18:51:41 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	ray_sphere(t_data *data, t_vec orig, t_vec dir, t_hit *closest_hit)
{
	int			hit_any;
	t_hit		temp;
	t_sphere	*sphere;

	hit_any = 0;
	sphere = data->scene->sphere;
	while (sphere)
	{
		if (hit_sphere(orig, dir, *sphere, &temp))
		{
			if (temp.t > 0.001 && temp.t < closest_hit->t)
			{
				*closest_hit = temp;
				hit_any = 1;
			}
		}
		sphere = sphere->next;
	}
	return (hit_any);
}

int	ray_cylinder(t_data *data, t_vec orig, t_vec dir, t_hit *closest_hit)
{
	int			hit_any;
	t_hit		temp;
	t_cylinder	*cylinder;

	hit_any = 0;
	cylinder = data->scene->cylinder;
	while (cylinder)
	{
		if (hit_cylinder(orig, dir, *cylinder, &temp))
		{
			if (temp.t > 0.001 && temp.t < closest_hit->t)
			{
				*closest_hit = temp;
				hit_any = 1;
			}
		}
		cylinder = cylinder->next;
	}
	return (hit_any);
}

int	ray_plane(t_data *data, t_vec orig, t_vec dir, t_hit *closest_hit)
{
	int			hit_any;
	t_hit		temp;
	t_plane		*plane;

	hit_any = 0;
	plane = data->scene->plane;
	while (plane)
	{
		if (hit_plane(orig, dir, *plane, &temp))
		{
			if (temp.t > 0.001 && temp.t < closest_hit->t)
			{
				*closest_hit = temp;
				hit_any = 1;
			}
		}
		plane = plane->next;
	}
	return (hit_any);
}
