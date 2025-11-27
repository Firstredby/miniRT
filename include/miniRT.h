/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:26:13 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 11:26:15 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <mlx.h>
# include <limits.h>

# include "vector.h"
# include "color.h"
# include "lights.h"
# include "shapes.h"
# include "camera.h"
# include "render.h"
# include "parsing.h"

# ifdef DEBUG
#  define DEBUG_ON 1
# else
#  define DEBUG_ON 0
# endif

# define PI 3.141592653589793
# define WIDTH  1024
# define HEIGHT 768

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_scene		*scene;
}	t_data;

int		moving(int keycode, t_data *data);

#endif