#ifndef LIGHTS_H
# define LIGHTS_H

# include "vector.h"
# include "color.h"

struct s_hit;
struct s_scene;

typedef struct s_light
{
	t_vec	pos;
	t_color	color;
	double	brightness;
	struct s_light	*next;
}	t_light;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

t_color ambient(t_color scene, t_color color, double intensity);
t_color diffuse(struct s_hit hit, t_light light);
t_color specular(struct s_hit hit, t_light light, t_vec cam_pos, double shininess);
int     in_shadow(struct s_hit *hit, struct s_scene *scene);

#endif
