#include "miniRT.h"

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

t_vec vec_norm(t_vec v)
{
    double len = sqrt(vec_dot(v, v));
    return vec(v.x / len, v.y / len, v.z / len);
}