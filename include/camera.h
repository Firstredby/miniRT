#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "color.h"

struct s_data;

typedef struct s_camera
{
	t_vec	cam;
	t_vec	dir;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	fov;
	double	aspect;
	double	scale;
}	t_camera;

void    axis_prep(struct s_data *data);

#endif
