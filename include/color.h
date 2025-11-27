/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:23:51 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 21:50:35 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

t_color	color(int c);
int		color_to_int(t_color c);
t_color	color_scale(t_color c, double k);
t_color	color_add(t_color c1, t_color c2);
t_color	color_mul(t_color c1, t_color c2);

#endif
