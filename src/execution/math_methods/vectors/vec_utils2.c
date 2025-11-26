#include "../../../../include/miniRT.h"

t_vec vec_norm(t_vec v)
{
    double len = sqrt(vec_dot(v, v));
    return vec(v.x / len, v.y / len, v.z / len);
}

t_vec vec_cross(t_vec a, t_vec b)
{
    return (t_vec){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}