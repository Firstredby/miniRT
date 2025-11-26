#include "miniRT.h"

t_vec rotate_axis(t_vec v, t_vec axis, double angle)
{
    double c = cos(angle);
    double s = sin(angle);
    return vec_add(
        vec_add(
            vec_scale(v, c),
            vec_scale(vec_cross(axis, v), s)
        ),
        vec_scale(axis, vec_dot(axis, v) * (1 - c))
    );
}

t_vec rotate_y(t_vec v, double angle)
{
    double c = cos(angle);
    double s = sin(angle);

    return (t_vec){
        v.x * c + v.z * s,
        v.y,
        -v.x * s + v.z * c
    };
}

int	moving(int keycode, t_data *data)
{
	if (keycode == 'w')
		data->pov->cam = vec_add(data->pov->cam, vec_scale(data->pov->forward, 0.2));
	else if (keycode == 's')
		data->pov->cam = vec_sub(data->pov->cam, vec_scale(data->pov->forward, 0.2));
	else if (keycode == 'd')
		data->pov->cam = vec_add(data->pov->cam, vec_scale(data->pov->right, 0.2));
	else if (keycode == 'a')
		data->pov->cam = vec_sub(data->pov->cam, vec_scale(data->pov->right, 0.2));
	else if (keycode == ' ')
		data->pov->cam = vec_add(data->pov->cam, vec_scale(data->pov->up, 0.2));
	else if (keycode == 'c')
		data->pov->cam = vec_sub(data->pov->cam, vec_scale(data->pov->up, 0.2));
	else if (keycode == 65362)
		data->pov->dir = rotate_axis(data->pov->dir, data->pov->right, 0.05);
	else if (keycode == 65364)
		data->pov->dir = rotate_axis(data->pov->dir, data->pov->right, -0.05);
	else if (keycode == 65363)
		data->pov->dir = rotate_y(data->pov->dir, -0.05);
	else if (keycode == 65361)
		data->pov->dir = rotate_y(data->pov->dir, 0.05);
	clear_image(data->img);
	render_scene(data);
	return (0);
}