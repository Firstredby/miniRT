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
} t_cylinder;


#endif