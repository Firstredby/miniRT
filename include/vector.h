#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

double  discriminant(double a, double b, double c);
t_vec   vec(double x, double y, double z);
t_vec   vec_add(t_vec a, t_vec b);
t_vec   vec_sub(t_vec a, t_vec b);
t_vec   vec_scale(t_vec v, double s);
double  vec_dot(t_vec a, t_vec b);
t_vec   vec_norm(t_vec v);
t_vec   vec_cross(t_vec a, t_vec b);


#endif
