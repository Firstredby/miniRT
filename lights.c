#include "miniRT.h"

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