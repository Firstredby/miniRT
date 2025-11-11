#include "miniRT.h"

t_vec vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 'w')
		data->pov->cam.z -= 0.2;
	else if (keycode == 's')
		data->pov->cam.z += 0.2;
	else if (keycode == 'a')
		data->pov->cam.x -= 0.2;
	else if (keycode == 'd')
		data->pov->cam.x += 0.2;
	else if (keycode == ' ')
		data->pov->cam.y += 0.2;
	else if (keycode == 'c')
		data->pov->cam.y -= 0.2;
	clear_image(data->img);
	render_scene(data);
	return (0);
}

int main(void)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	t_img	img;
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t_pov	pov = {
		.cam = vec(0, 0, 0),
		.fov = 90.0
	};
	t_shapes	shapes = {
		.ambient = { .ratio = 0.1, .color = color(0xFFFFFF)},
		// .cylinder = {.center = vec(50, 0, 20.6), .axis = vec_norm(vec(0, 0, 1)),
		// 		.radius = 14.2, .height = 21.42, .color = 0x00FF00},
		.sphere = { vec(0.0, 0.0, -5.0), 3, 0xFF0000 },
		// .plane = {.center = vec(0, 0, -10), .axis = vec_norm(vec(0, 1, 0)),
		// 		.color = 0x0000FF},
		.light = { .pos = vec(4, 0, 1), .brightness = 0.6,
				.color = color(0xFFFFFF) }
	};
	t_data	data = {
		.mlx_ptr = mlx,
		.win_ptr = win,
		.img = &img,
		.pov = &pov,
		.shapes = &shapes
	};
	render_scene(&data);
	mlx_key_hook(win, handle_key, &data);
	mlx_loop(mlx);
	return 0;
}
