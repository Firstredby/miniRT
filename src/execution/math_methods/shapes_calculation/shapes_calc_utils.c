/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_calc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:57:16 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/27 13:21:47 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/miniRT.h"

int	cyltop(t_cylinder cyl, t_vec orig, t_vec dir, t_hit *hit)
{
	t_vec	side;
	t_vec	p;
	double	denom;
	double	t;
	double	dist;

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
	double	t;
	double	dist;

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
