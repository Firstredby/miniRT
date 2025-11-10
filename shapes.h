#ifndef SHAPES_H
#define SHAPES_H

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_sphere {
    t_vec	center;
    double	radius;
    int		color;
}   t_sphere;

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	axis;
	double	radius;
	double	height;
	int		color;
}	t_cylinder;

typedef struct s_plane
{
	t_vec	center;
	t_vec	axis;
	int		color;
}	t_plane;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
} t_color;

typedef	struct s_light
{
	t_vec	pos;
	t_color	color;
	double	brightness;
} t_light;


typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
	t_color	color;
}	t_hit;





#endif