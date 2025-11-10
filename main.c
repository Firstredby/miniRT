#include "miniRT.h"

t_vec vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

t_color	color(int c) // FFFFFF → 255,255,255
{
	t_color col;
	col.r = ((c >> 16) & 0xFF) / 255.0; // convert first two cymb
	col.g = ((c >> 8) & 0xFF) / 255.0;	// convert next two cymb
	col.b = (c & 0xFF) / 255.0; // convert last two cymb
	return col;
}

int color_to_int(t_color c) // 255,255,255 → FFFFFF
{
    int r = fmin(255, fmax(0, (int)(c.r * 255)));
    int g = fmin(255, fmax(0, (int)(c.g * 255)));
    int b = fmin(255, fmax(0, (int)(c.b * 255)));
    return (r << 16) | (g << 8) | b;
}

t_color	color_scale(t_color c, double k)
{
	t_color res;
    res.r = c.r * k;
    res.g = c.g * k;
    res.b = c.b * k;
    return res;
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color res;
    res.r = c1.r + c2.r;
    res.g = c1.g + c2.g;
    res.b = c1.b + c2.b;
    return res;
}

t_color	color_mul(t_color c1, t_color c2)
{
	t_color res;
    res.r = c1.r * c2.r;
    res.g = c1.g * c2.g;
    res.b = c1.b * c2.b;
    return res;
}

t_color ambient(t_color obj_c, double intensity)
{
    return color_scale(obj_c, intensity);
}
t_color	diffuse(t_hit hit, t_light light)
{
	t_vec L = vec_norm(vec_sub(light.pos, hit.point));
	double dot = fmax(0.0, vec_dot(hit.normal, L));
	return (color_scale(color_mul(hit.color, light.color), dot * light.brightness));
}

int hit_sphere(t_vec orig, t_vec dir, t_sphere s, t_hit *hit)
{
    t_vec oc = vec_sub(orig, s.center);
    double a = vec_dot(dir, dir);
    double b = 2.0 * vec_dot(oc, dir);
    double c = vec_dot(oc, oc) - s.radius * s.radius;
	double disc = discriminant(a, b, c);
	if (discriminant < 0)
    	return (0);
	double t1 = (-b - sqrt(disc)) / (2 * a);
	double t2 = (-b + sqrt(disc)) / (2 * a);
	double t;
	if (t1 > 0)
		t = t1;
	else if (t2 > 0)
		t = t2;
	else
		return (0);
	hit->t = t;
	hit->point = vec_add(orig, vec_scale(dir, t));
	hit->normal = vec_norm(vec_sub(hit->point, s.center));
	hit->color = color(s.color);
	return (1);
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

int	hit_cylinder(t_vec orig, t_vec dir, t_cylinder cyl, t_hit *hit)
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
	hit->t = t;
	hit->point = vec_add(orig, vec_scale(dir, t));
	hit->normal = vec_norm(vec_sub(hit->point, cyl.center));
	hit->color = color(cyl.color);
	if (t > 0)
	{
		t_vec p = vec_add(orig, vec_scale(dir, t));
		double h_proj = vec_dot(vec_sub(p, cyl.center), cyl.axis);
		if (h_proj >= -cyl.height / 2 && h_proj <= cyl.height / 2)
			return (1);
	}
	if (cyledges(cyl, top_center, orig, dir) || cyledges(cyl, bottom_center, orig, dir))
		return (1);
	return (0);
}

int	hit_plane(t_vec orig, t_vec dir, t_plane pl, t_hit *hit)
{
	double denom = vec_dot(dir, pl.axis);
    if (fabs(denom) < 1e-6)
        return (0);
    double t = -vec_dot(vec_sub(orig, pl.center), pl.axis) / denom;
	hit->t = t;
	hit->point = vec_add(orig, vec_scale(dir, t));
	hit->normal = vec_norm(vec_sub(hit->point, pl.center));
	hit->color = color(pl.color);
    if (t < 0)
        return (0);
    return (1);
}

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
    t_vec cam = vec(0, 0, 0);
    t_sphere sph = { vec(-3, 0, -5), 1.0, 0xFFFFFF };
	t_cylinder cyl = {.center = vec(3, 0, -5), .axis = vec_norm(vec(0, 1, 1)), .radius = 1.0, .height = 3.0, .color = 0x00FF00};
	t_plane	pl = {.center = vec(0, 0, -4), .axis = vec_norm(vec(-1, 1, 1)), .color = 0x000000};
	t_light li = {.pos = vec(0, -1, -1), .brightness = 0.6, .color = color(0xAAFFFF)};
	t_hit	hit;
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

            if (hit_sphere(cam, dir, sph, &hit))
			{
				t_color base = color(sph.color);
				t_color ambient_col = color_scale(base, 0.1);
				t_color diffuse_col = diffuse(hit, li); // diffuse тоже возвращает t_color
				t_color final_col = color_add(ambient_col, diffuse_col);
				int pixel_color = color_to_int(final_col);
                mlx_pixel_put(mlx, win, x, y, pixel_color);
			}
			else if (hit_cylinder(cam, dir, cyl, &hit))
			{
				t_color base = color(sph.color);
				t_color ambient_col = color_scale(base, 0.1);
				t_color diffuse_col = diffuse(hit, li); // diffuse тоже возвращает t_color
				t_color final_col = color_add(ambient_col, diffuse_col);
				int pixel_color = color_to_int(final_col);
                mlx_pixel_put(mlx, win, x, y, pixel_color);
			}
			else if (hit_plane(cam, dir, pl, &hit))
			{
				t_color base = color(sph.color);
				t_color ambient_col = color_scale(base, 0.1);
				t_color diffuse_col = diffuse(hit, li); // diffuse тоже возвращает t_color
				t_color final_col = color_add(ambient_col, diffuse_col);
				int pixel_color = color_to_int(final_col);
                mlx_pixel_put(mlx, win, x, y, pixel_color);
			}
            else
                mlx_pixel_put(mlx, win, x, y, 0x888888); // фон
        }
    }

    mlx_loop(mlx);
    return 0;
}