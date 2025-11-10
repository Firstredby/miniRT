#include "miniRT.h"

t_color	color(int c)
{
	t_color col;
	col.r = ((c >> 16) & 0xFF) / 255.0; // convert first two cymb
	col.g = ((c >> 8) & 0xFF) / 255.0;	// convert next two cymb
	col.b = (c & 0xFF) / 255.0; // convert last two cymb
	return col;
}

int color_to_int(t_color c)
{
	//vice versa color(int c)
    int r = fmin(255, fmax(0, (int)(c.r * 255)));
    int g = fmin(255, fmax(0, (int)(c.g * 255)));
    int b = fmin(255, fmax(0, (int)(c.b * 255)));
    return (r << 16) | (g << 8) | b;
}

t_color	color_scale(t_color c, double k)
{
	t_color res;
    res.r = c.r * k;
    res.g = c.g * k;
    res.b = c.b * k;
    return res;
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color res;
    res.r = c1.r + c2.r;
    res.g = c1.g + c2.g;
    res.b = c1.b + c2.b;
    return res;
}

t_color	color_mul(t_color c1, t_color c2)
{
	t_color res;
    res.r = c1.r * c2.r;
    res.g = c1.g * c2.g;
    res.b = c1.b * c2.b;
    return res;
}
