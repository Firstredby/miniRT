#include "../include/miniRT.h"

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

	data->scene->camera->dir = vec_norm(data->scene->camera->dir);
	data->scene->camera->scale = tan((data->scene->camera->fov * 0.5) * PI / 180);
	data->scene->camera->aspect = (double)WIDTH / (double)HEIGHT;
	data->scene->camera->forward = vec_norm(data->scene->camera->dir);
	world_up = vec(0, 1, 0);
	data->scene->camera->right = vec_norm(vec_norm(vec_cross(data->scene->camera->forward, world_up)));
	data->scene->camera->up = vec_cross(data->scene->camera->right, data->scene->camera->forward);
}

void	scene_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	t_data	data;
	t_img	img;

	if (argc != 2)
		return (print_error("Usage: ./miniRT <scene_file.rt>\n"), 0);
	
	scene = parse_scene(argv[1]);
	if (!scene)
		return (0);
	data.scene = scene;
	scene_init(&data);
	img.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img,
						&img.bits_per_pixel,
						&img.line_length,
						&img.endian);
	data.img = &img;
	render_scene(&data);
	mlx_key_hook(data.win_ptr, &handle_key, &data);
	mlx_loop(data.mlx_ptr);
	free_scene(scene);
    return (0);
}
