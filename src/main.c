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

	data->pov->scale = tan((data->pov->fov * 0.5) * PI / 180);
	data->pov->aspect = (double)WIDTH / (double)HEIGHT;
	data->pov->forward = vec_norm(data->pov->dir);
	world_up = vec(0, 1, 0);
	data->pov->right = vec_norm(vec_norm(vec_cross(data->pov->forward, world_up)));
	data->pov->up = vec_cross(data->pov->right, data->pov->forward);
}

void	scene_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	data->img->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img,
						&data->img->bits_per_pixel,
						&data->img->line_length,
						&data->img->endian);

}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	t_data	data;

	if (argc != 2)
		return (print_error("Usage: ./miniRT <scene_file.rt>\n"), 0);
	scene = parse_scene(argv[1]);
	if (!scene)
		return (0);
	scene_init(&data);
	render_scene(&data);
	mlx_key_hook(data.win_ptr, &handle_key, &data);
	mlx_loop(data.mlx_ptr);
	free_scene(scene);
    return (0);
}
