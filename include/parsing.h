#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

# include "vector.h"
# include "color.h"
# include "lights.h"
# include "shapes.h"
# include "camera.h"
# include "../libft/libft.h"

# define ELEM_AMBIENT   1
# define ELEM_CAMERA    2
# define ELEM_LIGHT     3
# define ELEM_SPHERE    4
# define ELEM_PLANE     5
# define ELEM_CYLINDER  6
# define ELEM_UNKNOWN   0

typedef struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_cylinder	*cylinder;
	t_plane		*plane;
	t_light		*light;
	t_sphere	*sphere;
}	t_scene;

typedef struct s_tracking
{
	int		line_number;
	int		has_ambient;
	int		has_camera;
	int		light_count;
	int		object_cout;
	char	*filename;
}	t_tracking;

// parsing prototypes
int			parse_line(char *line, t_scene *scene, t_tracking *tracking);
int			parse_ambient(char *line, t_scene *scene, t_tracking *tracking);
int			parse_camera(char *line, t_scene *scene, t_tracking *tracking);
int			parse_light(char *line, t_scene *scene, t_tracking *tracking);
int			parse_sphere(char *line, t_scene *scene, t_tracking *tracking);
int			parse_plane(char *line, t_scene *scene, t_tracking *tracking);
int			parse_cylinder(char *line, t_scene *scene, t_tracking *tracking);
int			parse_vec(char *str, t_vec *vec);
int			parse_color(char *str, t_color *color);
int			parse_double(char *str, double *value);
int			parse_int(char *str, int *value);
int			parse_vec(char *str, t_vec *vec);
int			validate_normalized(t_vec v, char *ele);

t_scene		*parse_scene(char *filename);
int			validate_file(char *filename);
int			validate_scene(t_scene *scene, t_tracking *tracking);
int			empty_line(char *line);
char		*trim_whitespace(char *str);
int			is_whitespace(char c);

void		free_scene(t_scene *scene);
void		free_array(char **list);
int			count_array(char **array);

void		init_tracking(t_tracking *tracking);
t_scene		*init_scene(void);

// error
int			file_error(char *message, char *filename);
int			print_error(char *message);

#endif
