/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:26:37 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 21:56:28 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "vector.h"
# include "color.h"
# include "lights.h"
# include "shapes.h"
# include "camera.h"

struct	s_img;
struct	s_data;

typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
	t_color	color;
}	t_hit;

void	my_mlx_pixel_put(struct s_img *img, int x, int y, int color);
void	clear_image(struct s_img *img);
void	render_scene(struct s_data *data);
double	color_contrast(t_color c1, t_color c2);

#endif
