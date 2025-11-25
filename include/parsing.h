/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:43:35 by aorth             #+#    #+#             */
/*   Updated: 2025/11/25 12:23:28 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# define ELEM_AMBIENT   1
# define ELEM_CAMERA    2
# define ELEM_LIGHT     3
# define ELEM_SPHERE    4
# define ELEM_PLANE     5
# define ELEM_CYLINDER  6
# define ELEM_UNKNOWN   0

# include <stdlib.h>
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include "get_next_line.h"

typedef struct s_vec
{
    double x;
    double y;
    double z;
}               t_vec;

typedef struct s_color
{
    int r;
    int g;
    int b;
}               t_color;

typedef struct s_ambient
{
    double ratio;
    t_color color;
}               t_ambient;

typedef struct s_camera
{
    t_vec   pos;
    t_vec   orientation;
    int     fov;
}               t_camera;

typedef struct s_light
{
    t_vec		position;
	double		brightness;
	t_color		color;
	struct s_light	*next;
}               t_light;

typedef struct s_sphere
{
    t_vec		center;
	double		diameter;
	t_color		color;
	struct s_sphere	*next;
}               t_sphere;

typedef struct s_plane
{
	t_vec		point;
	t_vec		normal;
	t_color		color;
	struct s_plane	*next;
}	            t_plane;

typedef struct s_cylinder
{
	t_vec			center;
	t_vec			axis;
	double			diameter;
	double			height;
	t_color			color;
	struct s_cylinder	*next;
}	            t_cylinder;

typedef struct s_scene
{
    t_ambient *ambient;
    t_camera    *camera;
    t_cylinder  *cylinder;
    t_plane     *plane;
    t_light     *light;
    t_sphere    *sphere;
}               t_scene;

typedef struct s_tracking
{
    int line_number;
    int has_ambient;
    int has_camera;
    int light_count;
    int object_cout;
    char    *filename;
}               t_tracking;

//UTILS FUNCTIONS
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
t_scene *parse_scene(char *filename);
int validate_file(char *filename);
int empty_line(char *line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *trim_whitespace(char *str);
int is_whitespace(char c);
void	free_array(char **list);
int		count_array(char **array);
int	    ft_isdigit(int c);
long	ft_atoi(const char *nptr);
int parse_ambient(char *line, t_scene *scene, t_tracking *tracking);
int parse_line(char *line, t_scene *scene, t_tracking *tracking);
int parse_double(char *str, double *value);
int parse_color(char *str, t_color *color);
int	parse_camera(char *line, t_scene *scene, t_tracking *tracking);
int parse_vec(char *str, t_vec *vec);
int parse_int(char *str, int *value);
int validate_normalized(t_vec v, char *ele);
int parse_cylinder(char *line, t_scene *scene, t_tracking *tracking);
int parse_plane(char *line, t_scene *scene, t_tracking *tracking);
int parse_sphere(char *line, t_scene *scene, t_tracking *tracking);
int parse_light(char *line, t_scene *scene, t_tracking *tracking);
int validate_scene(t_scene *scene, t_tracking *tracking);
void    free_scene(t_scene *scene);
void	init_tracking(t_tracking *tracking);
t_scene	*init_scene(void);


//ERROR
int file_error(char *message, char *filename);
int print_error(char *message);

#endif