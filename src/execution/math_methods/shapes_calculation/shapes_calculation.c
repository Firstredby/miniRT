/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:54:02 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/27 20:48:31 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/miniRT.h"

int	hit_sphere(t_vec orig, t_vec dir, t_sphere s, t_hit *hit)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = vec_sub(orig, s.center);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(oc, dir);
	c = vec_dot(oc, oc) - s.radius * s.radius;
	disc = discriminant(a, b, c);
	if (disc < 0)
		return (0);
	hit->t = distance(disc, a, b);
	if (hit->t < 0)
		return (0);
	hit->point = vec_add(orig, vec_scale(dir, hit->t));
	hit->normal = vec_norm(vec_sub(hit->point, s.center));
	hit->color = s.color;
	return (1);
}

int	hit_cylinder(t_vec orig, t_vec dir, t_cylinder cyl, t_hit *hit)
{
	t_vec	oc;
	t_vec	p;
	double	abc[3];
	double	tmp;
	double	t;

	oc = vec_sub(orig, cyl.center);
	abc[0] = vec_dot(dir, dir) - pow(vec_dot(dir, cyl.axis), 2);
	abc[1] = 2 * (vec_dot(oc, dir) - vec_dot(oc, cyl.axis)
			* vec_dot(dir, cyl.axis));
	abc[2] = vec_dot(oc, oc) - pow(vec_dot(oc, cyl.axis), 2)
		- cyl.radius * cyl.radius;
	tmp = discriminant(abc[0], abc[1], abc[2]);
	if (tmp < 0)
		return (0);
	t = distance(tmp, abc[0], abc[1]);
	p = vec_add(orig, vec_scale(dir, t));
	tmp = vec_dot(vec_sub(p, cyl.center), cyl.axis);
	if (tmp < -cyl.height / 2 || tmp > cyl.height / 2)
		return (cyltop(cyl, orig, dir, hit) || cylbot(cyl, orig, dir, hit));
	hit->t = t;
	hit->point = p;
	hit->normal = vec_norm(vec_sub(vec_sub(p, cyl.center),
				vec_scale(cyl.axis, tmp)));
	return (hit->color = cyl.color, 1);
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
