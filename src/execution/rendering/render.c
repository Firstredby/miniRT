/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:01:59 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/28 19:05:50 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	trace_ray(t_data *data, t_vec orig, t_vec dir, t_hit *closest_hit)
{
	int	result;

	result = 0;
	closest_hit->t = 1e30;
	if (ray_sphere(data, orig, dir, closest_hit))
		result = 1;
	if (ray_cylinder(data, orig, dir, closest_hit))
		result = 1;
	if (ray_plane(data, orig, dir, closest_hit))
		result = 1;
	return (result);
}

t_color	shade_pixel(t_data *data, t_hit *hit)
{
	t_color	amb;
	t_color	diff;
	t_color	spec;
	t_color	final;

	amb = ambient(hit->color,
			data->scene->ambient->color,
			data->scene->ambient->ratio);
	final = amb;
	if (!in_shadow(hit, data->scene))
	{
		diff = diffuse(*hit, *data->scene->light);
		spec = specular(*hit, *data->scene->light,
				data->scene->camera->cam, 32.0);
		final = color_add(color_add(amb, diff), spec);
	}
	return (final);
}

t_color	render_single_ray(t_data *data, double px_x, double px_y)
{
	t_hit	hit;
	t_vec	ray;
	double	px;
	double	py;

	px = (2 * px_x / WIDTH - 1) * data->scene->camera->aspect
		* data->scene->camera->scale;
	py = (1 - 2 * px_y / HEIGHT) * data->scene->camera->scale;
	ray = vec_add(
			vec_add(
				vec_scale(data->scene->camera->right, px),
				vec_scale(data->scene->camera->up, py)),
			data->scene->camera->forward);
	if (trace_ray(data, data->scene->camera->cam, ray, &hit))
		return (shade_pixel(data, &hit));
	else
		return ((t_color){0, 0, 0});
}

t_color	render_pixel(t_data *data, int x, int y)
{
	t_color	corners[4];
	t_color	avg;
	int		i;
	int		j;

	corners[0] = render_single_ray(data, x, y);
	corners[1] = render_single_ray(data, x + 0.5, y);
	corners[2] = render_single_ray(data, x, y + 0.5);
	corners[3] = render_single_ray(data, x + 0.5, y + 0.5);
	i = 0;
	while (i++ < 3)
	{
		j = i;
		while (j < 4)
			color_contrast(corners[i - 1], corners[j++]);
	}
	avg = color(0x000000);
	while (i >= 0)
		avg = color_add(avg, corners[i--]);
	return (color_scale(avg, 0.25));
}

void	render_scene(t_data *data)
{
	t_color	c;
	int		y;
	int		x;

	x = 0;
	y = 0;
	axis_prep(data);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			c = render_pixel(data, x, y);
			my_mlx_pixel_put(data->img, x++, y, color_to_int(c));
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img->img, 0, 0);
}
