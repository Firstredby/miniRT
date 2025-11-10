#include "miniRT.h"

t_vec vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

int main(void)
{
    void		*mlx = mlx_init();
    void		*win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	t_img img;
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t_pov		pov = {
		.cam = vec(0, 0, 0)
	};
	t_shapes	shapes = {
		.ambient = { .ratio = 0.3, .color = color(0xFFFF88)},
		.cylinder = {.center = vec(3, 0, -5), .axis = vec_norm(vec(0, 1, 1)),
						.radius = 1.0, .height = 3.0, .color = 0x00FF00},
		.sphere = { vec(-3, 0, -5), 1.0, 0xFFFFFF },
		.plane = {.center = vec(0, 0, -4), .axis = vec_norm(vec(-1, 1, 1)),
						.color = 0x000000},
		.light = {.pos = vec(0.0, -1.0, -1.0), .brightness = 0.6,
						.color = color(0xAAFFFF)}
	};
	t_hit		hit;
	t_data		data = {
		.mlx_ptr = mlx,
		.win_ptr = win,
		.img = &img,
		.pov = &pov,
		.shapes = &shapes
	};

    double		fov = 100.0;
    double		scale = tan((fov * 0.5) * PI / 180);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            pov.x = (2 * (x + 0.5) / (double)WIDTH - 1) * scale * (WIDTH / (double)HEIGHT);
            pov.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
            pov.dir = vec_norm(vec(pov.x, pov.y, -2));
            if (hit_sphere(pov.cam, pov.dir, shapes.sphere, &hit))
				render(&data, &hit, &shapes, x, y);
			else if (hit_cylinder(pov.cam, pov.dir, shapes.cylinder, &hit))
				render(&data, &hit, &shapes, x, y);
			else if (hit_plane(pov.cam, pov.dir, shapes.plane, &hit))
				render(&data, &hit, &shapes, x, y);
            else
                my_mlx_pixel_put(data.img, x, y, 0x888888);
        }
    }
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
    mlx_loop(mlx);
    return 0;
}
