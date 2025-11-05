#include "miniRT.h"

t_vec vec(double x, double y, double z) 
{
	return (t_vec){x, y, z};
}

t_vec vec_add(t_vec a, t_vec b) {
    return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec vec_sub(t_vec a, t_vec b) {
    return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec vec_scale(t_vec v, double s) {
    return vec(v.x * s, v.y * s, v.z * s);
}

double vec_dot(t_vec a, t_vec b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec vec_norm(t_vec v) {
    double len = sqrt(vec_dot(v, v));
    return vec(v.x / len, v.y / len, v.z / len);
}

int hit_sphere(t_vec orig, t_vec dir, t_sphere s)
{
    t_vec oc = vec_sub(orig, s.center);
    double a = vec_dot(dir, dir);
    double b = 2.0 * vec_dot(oc, dir);
    double c = vec_dot(oc, oc) - s.radius * s.radius;
    return (discriminant(a, b, c) > 0);
}

int	cyledges(t_cylinder cyl, t_vec side, t_vec orig, t_vec dir)
{
	double denom_top = vec_dot(dir, cyl.axis);
	if (fabs(denom_top) > 1e-6)
	{
		double t_top = vec_dot(vec_sub(side, orig), cyl.axis) / denom_top;
		if (t_top > 0)
		{
			t_vec p_top = vec_add(orig, vec_scale(dir, t_top));
			double dist = vec_dot(vec_sub(p_top, side), vec_sub(p_top, side));
			if (dist <= cyl.radius * cyl.radius)
				return (1);
		}
	}
	return (0);
}

int	hit_cylinder(t_vec orig, t_vec dir, t_cylinder cyl)
{
	t_vec oc = vec_sub(orig, cyl.center);
	t_vec top_center = vec_add(cyl.center, vec_scale(cyl.axis, cyl.height / 2));
	t_vec bottom_center = vec_sub(cyl.center, vec_scale(cyl.axis, cyl.height / 2));
	double	a = vec_dot(dir, dir) - pow(vec_dot(dir, cyl.axis), 2);
	double	b = 2 * (vec_dot(oc, dir) - vec_dot(oc, cyl.axis) * vec_dot(dir, cyl.axis));
	double	c = vec_dot(oc, oc) - pow(vec_dot(oc, cyl.axis), 2) - cyl.radius * cyl.radius;
	if (discriminant(a, b, c) < 0)
		return (0);
	double	h1 = (-b + sqrt(discriminant(a, b, c))) / (2 * a);
	double	h2 = (-b - sqrt(discriminant(a, b, c))) / (2 * a);
	double	t;
	if (h1 > 0 && h2 > 0)
	{
		if (h1 > h2)
			t = h2;
		else
			t = h1;
	}
	else if (h1 > 0)
		t = h1;
	else if (h2 > 0)
		t = h2;
	else
		t = -1;
	if (t > 0)
	{
		t_vec p = vec_add(orig, vec_scale(dir, t));
		double h_proj = vec_dot(vec_sub(p, cyl.center), cyl.axis);
		if (h_proj >= -cyl.height / 2 && h_proj <= cyl.height / 2)
			return (1);
	}
	if (cyledges(cyl, top_center, orig, dir))
		return (1);
	else if (cyledges(cyl, bottom_center, orig, dir))
		return (1);
	else
		return (0);
}

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
    t_vec cam = vec(0, 0, 0);
    t_sphere sphere = { vec(-3, 0, -5), 1.0, 0xFFFFFF };
	t_cylinder cyl = {.center = vec(3, 0, -5), .axis = vec_norm(vec(0, 1, 0)), .radius = 1.0, .height = 3.0, .color = 0x00FF00};
	t_vec dir;
	double px;
	double py;

    double fov = 100.0;
    double scale = tan((fov * 0.5) * PI / 180);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            px = (2 * (x + 0.5) / (double)WIDTH - 1) * scale * (WIDTH / (double)HEIGHT);
            py = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;

            dir = vec_norm(vec(px, py, -1));

            if (hit_sphere(cam, dir, sphere) || hit_cylinder(cam, dir, cyl))
                mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
            else
                mlx_pixel_put(mlx, win, x, y, 0x808080); // фон
        }
    }

    mlx_loop(mlx);
    return 0;
}