#include "miniRT.h"

int	handle_key(int keycode, t_data *data)
{
	(void)data;
	if (DEBUG_ON)
		moving(keycode, data);
	if (keycode == 65307)
		exit(0);
	return (0);
}

void	axis_prep(t_data *data)
{
	t_vec	world_up;

	data->pov->scale = tan((data->pov->fov * 0.5) * PI / 180);
	data->pov->aspect = (double)WIDTH / (double)HEIGHT;
	data->pov->forward = vec_norm(data->pov->dir);
	world_up = vec(0, 1, 0);
	data->pov->right = vec_norm(vec_norm(vec_cross(data->pov->forward, world_up)));
	data->pov->up = vec_cross(data->pov->right, data->pov->forward);
}

int main(void)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	t_img	img;
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t_pov	pov = {
		.cam = vec(7, 0, -5.0),
		.dir = vec_norm((t_vec){-1, 0, 0}),
		.fov = 70.0
	};
	t_shapes	shapes = {
		 .ambient = { .ratio = 0.15, .color = color(0x222222) },
		.cylinder = {
			.center = vec(0.0, -0.5, -5.0),
			.axis = vec_norm(vec(0.0, 1.0, 0.0)),
			.radius = 1.0,
			.height = 3.0,
			.color = 0xCC4444
		},
		.plane = {
			.center = vec(0.0, -2.0, -5.0),
			.axis = vec_norm(vec(0.0, 1.0, 0.0)),
			.color = 0x222222
		},
		.sphere = {
			.center = vec(-3.0, 0.0, -6.0),
			.radius = 0.8,
			.color = 0x00CCFF
		},
		.light = {
			.pos = vec(3.0, 4.0, -2.0),
			.brightness = 1.0,
			.color = color(0xFFFFFF)
		}
	};
	t_data	data = {
		.mlx_ptr = mlx,
		.win_ptr = win,
		.img = &img,
		.pov = &pov,
		.shapes = &shapes
	};
	render_scene(&data);
	mlx_key_hook(win, &handle_key, &data);
	mlx_loop(mlx);
	return 0;
}
