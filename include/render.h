#ifndef RENDER_H
# define RENDER_H

# include "vector.h"
# include "color.h"
# include "lights.h"
# include "shapes.h"
# include "camera.h"

struct s_img;
struct s_data;

typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
	t_color	color;
}	t_hit;

void    my_mlx_pixel_put(struct s_img *img, int x, int y, int color);
void    render_pixel(struct s_data *data, t_hit *hit, int x, int y);
void    render_scene(struct s_data *data);
void    clear_image(struct s_img *img);

#endif
