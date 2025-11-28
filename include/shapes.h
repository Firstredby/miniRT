/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:27:18 by aorth             #+#    #+#             */
/*   Updated: 2025/11/28 19:07:53 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "vector.h"
# include "color.h"
# include "lights.h"

struct	s_hit;

typedef struct s_sphere
{
	t_vec				center;
	double				radius;
	t_color				color;
	struct s_sphere		*next;
}	t_sphere;

typedef struct s_plane
{
	t_vec				center;
	t_vec				axis;
	t_color				color;
	struct s_plane		*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vec				center;
	t_vec				axis;
	double				radius;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}	t_cylinder;

int	hit_sphere(t_vec orig, t_vec dir, t_sphere s, struct s_hit *hit);
int	hit_plane(t_vec orig, t_vec dir, t_plane pl, struct s_hit *hit);
int	cyltop(t_cylinder cyl, t_vec orig, t_vec dir, struct s_hit *hit);
int	cylbot(t_cylinder cyl, t_vec orig, t_vec dir, struct s_hit *hit);
int	hit_cylinder(t_vec orig, t_vec dir, t_cylinder cyl, struct s_hit *hit);

#endif
