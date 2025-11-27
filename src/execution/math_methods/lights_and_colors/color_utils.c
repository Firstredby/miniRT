/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:25:58 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/27 15:29:03 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/miniRT.h"

t_color	color(int c)
{
	t_color	col;

	col.r = ((c >> 16) & 0xFF) / 255.0;
	col.g = ((c >> 8) & 0xFF) / 255.0;
	col.b = (c & 0xFF) / 255.0;
	return (col);
}

int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = fmin(255, fmax(0, (int)(c.r * 255)));
	g = fmin(255, fmax(0, (int)(c.g * 255)));
	b = fmin(255, fmax(0, (int)(c.b * 255)));
	return ((r << 16) | (g << 8) | b);
}

t_color	color_scale(t_color c, double k)
{
	t_color	res;

	res.r = c.r * k;
	res.g = c.g * k;
	res.b = c.b * k;
	return (res);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	res;

	res.r = c1.r + c2.r;
	res.g = c1.g + c2.g;
	res.b = c1.b + c2.b;
	return (res);
}

t_color	color_mul(t_color c1, t_color c2)
{
	t_color	res;

	res.r = c1.r * c2.r;
	res.g = c1.g * c2.g;
	res.b = c1.b * c2.b;
	return (res);
}
