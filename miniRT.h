#ifndef MINIRT_H
#define MINIRT_H

#include "unistd.h"
#include "math.h"
#include "mlx.h"
#include "shapes.h"

#define PI 3.141592653589793
#define WIDTH  800
#define HEIGHT 600

double	discriminant(double a, double b, double c);
t_vec vec(double x, double y, double z);
t_vec vec_add(t_vec a, t_vec b);
t_vec vec_sub(t_vec a, t_vec b);
t_vec vec_scale(t_vec v, double s);
double vec_dot(t_vec a, t_vec b);
t_vec vec_norm(t_vec v);

#endif