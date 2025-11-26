#include "miniRT.h"

t_vec vec(double x, double y, double z)
{
	return (t_vec){ .x = x, .y = y, .z = z};
}

t_vec vec_add(t_vec a, t_vec b)
{
    return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec vec_sub(t_vec a, t_vec b)
{
    return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec vec_scale(t_vec v, double s)
{
    return vec(v.x * s, v.y * s, v.z * s);
}

double vec_dot(t_vec a, t_vec b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
