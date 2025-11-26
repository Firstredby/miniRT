#include "../../../../include/miniRT.h"

t_color ambient(t_color scene, t_color color, double intensity)
{
    return color_scale(color_mul(scene, color), intensity);
}

t_color	diffuse(t_hit hit, t_light light)
{
	t_vec L = vec_norm(vec_sub(light.pos, hit.point));
	double dot = fmax(0.0, vec_dot(hit.normal, L));
	return (color_scale(color_mul(hit.color, light.color), dot * light.brightness));
}

t_color	specular(t_hit hit, t_light light, t_vec cam_pos, double shininess)
{
	t_vec L = vec_norm(vec_sub(light.pos, hit.point));
	t_vec V = vec_norm(vec_sub(cam_pos, hit.point));
	t_vec R = vec_norm(vec_sub(vec_scale(hit.normal, 2 * vec_dot(hit.normal, L)), L));

	double spec = pow(fmax(vec_dot(R, V), 0.0), shininess);
	return color_scale(light.color, spec * light.brightness);
}

int	in_shadow(t_hit *hit, t_shapes *shapes)
{
	t_vec L = vec_norm(vec_sub(shapes->light->pos, hit->point));
	t_vec shadow_orig = vec_add(hit->point, vec_scale(hit->normal, 1e-4));
	t_hit shadow_hit;

	if (hit_sphere(shadow_orig, L, *shapes->sphere, &shadow_hit))
	{
		double light_dist = sqrt(vec_dot(vec_sub(shapes->light->pos, hit->point),
							vec_sub(shapes->light->pos, hit->point)));
		if (shadow_hit.t > 0 && shadow_hit.t < light_dist)
			return (1);
	}
	else if (hit_cylinder(shadow_orig, L, *shapes->cylinder, &shadow_hit))
	{
		double light_dist = sqrt(vec_dot(vec_sub(shapes->light->pos, hit->point),
							vec_sub(shapes->light->pos, hit->point)));
		if (shadow_hit.t > 0 && shadow_hit.t < light_dist)
			return (1);
	}
	return (0);
}