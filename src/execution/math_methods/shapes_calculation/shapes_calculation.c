#include "../../../../include/miniRT.h"

int hit_sphere(t_vec orig, t_vec dir, t_sphere s, t_hit *hit)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t1;
	double	t2;
	double	t;

	oc = vec_sub(orig, s.center);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(oc, dir);
	c = vec_dot(oc, oc) - s.radius * s.radius;
	disc = discriminant(a, b, c);
	if (disc < 0)
		return (0);
	t1 = (-b - sqrt(disc)) / (2 * a);
	t2 = (-b + sqrt(disc)) / (2 * a);
	if (t1 > 0)
		t = t1;
	else if (t2 > 0)
		t = t2;
	else
		return (0);
	hit->t = t;
	hit->point = vec_add(orig, vec_scale(dir, t));
	hit->normal = vec_norm(vec_sub(hit->point, s.center));
	hit->color = s.color;
	return (1);
}

int	cyltop(t_cylinder cyl, t_vec orig, t_vec dir, t_hit *hit)
{
	t_vec	side;
	t_vec	p;
	double	denom;
	double t;
	double dist;

	denom = vec_dot(dir, cyl.axis);
	side = vec_add(cyl.center, vec_scale(cyl.axis, cyl.height / 2));
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(side, orig), cyl.axis) / denom;
		if (t > 0)
		{
			p = vec_add(orig, vec_scale(dir, t));
			dist = vec_dot(vec_sub(p, side), vec_sub(p, side));
			if (dist <= cyl.radius * cyl.radius)
			{
			    hit->t = t;
			    hit->point = p;
				hit->normal = cyl.axis;
			    return (hit->color = cyl.color, 1);
			}
		}
	}
	return (0);
}

int	cylbot(t_cylinder cyl, t_vec orig, t_vec dir, t_hit *hit)
{
	t_vec	side;
	t_vec	p;
	double	denom;
	double t;
	double dist;

	denom = vec_dot(dir, cyl.axis);
	side = vec_sub(cyl.center, vec_scale(cyl.axis, cyl.height / 2));
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(side, orig), cyl.axis) / denom;
		if (t > 0)
		{
			p = vec_add(orig, vec_scale(dir, t));
			dist = vec_dot(vec_sub(p, side), vec_sub(p, side));
			if (dist <= cyl.radius * cyl.radius)
			{
			    hit->t = t;
			    hit->point = p;
				hit->normal = vec_scale(cyl.axis, -1);
			    return (hit->color = cyl.color, 1);
			}
		}
	}
	return (0);
}

int	hit_cylinder(t_vec orig, t_vec dir, t_cylinder cyl, t_hit *hit)
{
	t_vec	oc;
	t_vec	p;
	t_vec	normal;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t1;
	double	t2;
	double	t;
	double	h_proj;

	oc = vec_sub(orig, cyl.center);
	a = vec_dot(dir, dir) - pow(vec_dot(dir, cyl.axis), 2);
	b = 2 * (vec_dot(oc, dir) - vec_dot(oc, cyl.axis) * vec_dot(dir, cyl.axis));
	c = vec_dot(oc, oc) - pow(vec_dot(oc, cyl.axis), 2) - cyl.radius * cyl.radius;
	disc = discriminant(a, b, c);
	if (disc < 0)
		return (0);
	t1 = (-b + sqrt(disc)) / (2 * a);
	t2 = (-b - sqrt(disc)) / (2 * a);
	if (t1 > 0 && t2 > 0)
		t = fmin(t1, t2);
	else if (t1 > 0)
		t = t1;
	else if (t2 > 0)
		t = t2;
	else
		return (0);
	p = vec_add(orig, vec_scale(dir, t));
	h_proj = vec_dot(vec_sub(p, cyl.center), cyl.axis);
	if (h_proj < -cyl.height / 2 || h_proj > cyl.height / 2)
		return (cyltop(cyl, orig, dir, hit)
			|| cylbot(cyl, orig, dir, hit));
	normal = vec_norm(vec_sub(vec_sub(p, cyl.center),
						vec_scale(cyl.axis, h_proj)));
	hit->t = t;
	hit->point = p;
	hit->normal = normal;
	hit->color = cyl.color;
	return (1);
}

int	hit_plane(t_vec orig, t_vec dir, t_plane pl, t_hit *hit)
{
	double	denom;
	double	t;

	denom = vec_dot(dir, pl.axis);
	if (fabs(denom) < 1e-6)
		return (0);
	t = -vec_dot(vec_sub(orig, pl.center), pl.axis) / denom;
	if (t < 0)
		return (0);
	hit->t = t;
	hit->point = vec_add(orig, vec_scale(dir, t));
	hit->normal = pl.axis;
	hit->color = pl.color;
	return (1);
}