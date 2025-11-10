#ifndef MINIRT_H
#define MINIRT_H

#include "unistd.h"
#include "math.h"
#include "mlx.h"
#include "shapes.h"

#define PI 3.141592653589793
#define WIDTH  800
#define HEIGHT 600

typedef	struct s_light
{
	t_vec	pos;
	t_color	color;
	double	brightness;
}	t_light;


typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
	t_color	color;
}	t_hit;

typedef	struct s_shapes
{
	t_plane 	plane;
	t_cylinder	cylinder;
	t_sphere	sphere;
	t_light		light;
	t_ambient	ambient;
}	t_shapes;

typedef	struct s_pov
{
	t_vec	cam;
	t_vec	dir;
	double	x;
	double	y;
}	t_pov;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef	struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_shapes	*shapes;
	t_pov		*pov;
}	t_data;

//math------------------------------------------------------------
//----------------------------vectors-----------------------------
double	discriminant(double a, double b, double c);
t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_scale(t_vec v, double s);
double	vec_dot(t_vec a, t_vec b);
t_vec	vec_norm(t_vec v);
//----------------------------color-------------------------------
t_color	color(int c); // FFFFFF → 255,255,255
int 	color_to_int(t_color c); // 255,255,255 → FFFFFF
t_color	color_scale(t_color c, double k);
t_color	color_add(t_color c1, t_color c2);
t_color	color_mul(t_color c1, t_color c2);

//lights----------------------------------------------------------
t_color ambient(t_color scene, t_color color, double intensity);
t_color	diffuse(t_hit hit, t_light light);

//render----------------------------------------------------------
void	my_mlx_pixel_put(t_img *img, int x, int y, int color); // buffering image
void	render(t_data *data, t_hit *hit, t_shapes *shapes, int x, int y); // ray calculation

//shapes_calculation----------------------------------------------
int		hit_sphere(t_vec orig, t_vec dir, t_sphere s, t_hit *hit);
int		cyltop(t_cylinder cyl, t_vec orig, t_vec dir, t_hit *hit);
int		cylbot(t_cylinder cyl, t_vec orig, t_vec dir, t_hit *hit);
int		hit_cylinder(t_vec orig, t_vec dir, t_cylinder cyl, t_hit *hit);
int		hit_plane(t_vec orig, t_vec dir, t_plane pl, t_hit *hit);

#endif