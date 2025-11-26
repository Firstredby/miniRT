#include "miniRT.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clear_image(t_img *img)
{
	ft_memset(img->addr, 0, HEIGHT * img->line_length);
}

void	render_pixel(t_data *data, t_hit *hit, t_shapes *shapes, int x, int y)
{
	t_color amb;
	t_color diff;
	t_color spec;
	t_color final;
	int pixel_color;
	amb = ambient(hit->color,
					shapes->ambient.color,
					shapes->ambient.ratio);
	final = amb;
	if (!in_shadow(hit, shapes))
	{
		diff = diffuse(*hit, shapes->light);
		spec = specular(*hit, shapes->light, data->pov->cam, 32.0);
		final = color_add(color_add(amb, diff), spec);
	}
	pixel_color = color_to_int(final);
	my_mlx_pixel_put(data->img, x, y, pixel_color);
}

int trace_ray(t_data *data, t_vec orig, t_vec dir, t_hit *closest_hit)
{
    t_hit temp;
    int hit_any = 0;

    closest_hit->t = 1e30;
    if (hit_sphere(orig, dir, data->shapes->sphere, &temp))
    {
        if (temp.t < closest_hit->t)
        {
            *closest_hit = temp;
            hit_any = 1;
        }
    }
    if (hit_cylinder(orig, dir, data->shapes->cylinder, &temp))
    {
        if (temp.t < closest_hit->t)
        {
            *closest_hit = temp;
            hit_any = 1;
        }
    }
    if (hit_plane(orig, dir, data->shapes->plane, &temp))
    {
        if (temp.t < closest_hit->t)
        {
            *closest_hit = temp;
            hit_any = 1;
        }
    }
    return hit_any;
}

void	render_scene(t_data *data)
{
	t_hit	hit;
	t_vec	ray;
	double	px;
	double	py;

	axis_prep(data);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			px = (2 * (x + 0.5) / WIDTH - 1) * data->pov->aspect * data->pov->scale;
			py = (1 - 2 * (y + 0.5) / HEIGHT) * data->pov->scale;
    		ray = vec_norm(vec_add(vec_add(vec_scale(data->pov->right, px),
					vec_scale(data->pov->up, py)), data->pov->forward));
            if (trace_ray(data, data->pov->cam, ray, &hit))
				render_pixel(data, &hit, data->shapes, x, y);
            else
				my_mlx_pixel_put(data->img, x, y, 0x000000);
        }
    }
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
}
