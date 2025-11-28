/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:53:04 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/28 19:06:56 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img)
{
	ft_memset(img->addr, 0, HEIGHT * img->line_length);
}

double	color_contrast(t_color c1, t_color c2)
{
	double	dr;
	double	dg;
	double	db;

	dr = fabs(c1.r - c2.r);
	dg = fabs(c1.g - c2.g);
	db = fabs(c1.b - c2.b);
	return ((dr + dg + db) / (3.0 * 255.0));
}
