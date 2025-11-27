/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:22:42 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 11:23:18 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "color.h"

struct	s_data;

typedef struct s_camera
{
	t_vec	cam;
	t_vec	dir;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	fov;
	double	aspect;
	double	scale;
}	t_camera;

void	axis_prep(struct s_data *data);

#endif
