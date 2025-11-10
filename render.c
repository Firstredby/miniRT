#include "miniRT.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render(t_data *data, t_hit *hit, t_shapes *shapes, int x, int y)
{
	t_color ambient_col;
	t_color diffuse_col;
	t_color final_col;
	int pixel_color;

	ambient_col = ambient(hit->color,
					shapes->ambient.color,
					shapes->ambient.ratio);
	diffuse_col = diffuse(*hit, shapes->light);
	final_col = color_add(ambient_col, diffuse_col);
	pixel_color = color_to_int(final_col);
	my_mlx_pixel_put(data->img, x, y, pixel_color);
}