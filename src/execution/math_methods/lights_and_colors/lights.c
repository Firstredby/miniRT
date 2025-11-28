/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:22:34 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/28 18:34:43 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/miniRT.h"

t_color	ambient(t_color scene, t_color color, double intensity)
{
	return (color_scale(color_mul(scene, color), intensity));
}

t_color	diffuse(t_hit hit, t_light light)
{
	t_vec	l;
	double	dot;

	l = vec_norm(vec_sub(light.pos, hit.point));
	dot = fmax(0.0, vec_dot(hit.normal, l));
	return (color_scale(color_mul(hit.color, light.color),
			dot * light.brightness));
}

t_color	specular(t_hit hit, t_light light, t_vec cam_pos, double shininess)
{
	t_vec	l;
	t_vec	v;
	t_vec	r;
	double	spec;

	l = vec_norm(vec_sub(light.pos, hit.point));
	v = vec_norm(vec_sub(cam_pos, hit.point));
	r = vec_norm(vec_sub(vec_scale(hit.normal, 2 * vec_dot(hit.normal, l)), l));
	spec = pow(fmax(vec_dot(r, v), 0.0), shininess);
	return (color_scale(light.color, spec * light.brightness));
}

int	in_shadow(t_hit *hit, t_scene *scene)
{
	t_vec	l;
	t_vec	shadow_orig;
	double	light_dist;

	l = vec_sub(scene->light->pos, hit->point);
	shadow_orig = vec_add(hit->point, vec_scale(hit->normal, 1e-3));
	light_dist = vec_dot(l, l);
	return (sphere_loop(l, shadow_orig, light_dist, scene)
		|| cylinder_loop(l, shadow_orig, light_dist, scene)
		|| plane_loop(l, shadow_orig, light_dist, scene));
}
