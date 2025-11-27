/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:03:05 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 19:11:52 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	identify_elem(char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'A' && is_whitespace(line[i + 1]))
		return (ELEM_AMBIENT);
	else if (line[i] == 'C' && is_whitespace(line[i + 1]))
		return (ELEM_CAMERA);
	else if (line[i] == 'L' && is_whitespace(line[i + 1]))
		return (ELEM_LIGHT);
	else if (line[i] == 'p')
	{
		if (line[i + 1] == 'l' && is_whitespace(line[i + 2]))
			return (ELEM_PLANE);
	}
	else if (line[i] == 's')
	{
		if (line[i + 1] == 'p' && is_whitespace(line[i + 2]))
			return (ELEM_SPHERE);
	}
	else if (line[i] == 'c')
	{
		if (line[i + 1] == 'y' && is_whitespace(line[i + 2]))
			return (ELEM_CYLINDER);
	}
	return (ELEM_UNKNOWN);
}

static int	process_element(char *new_line, int id, t_scene *scene,
	t_tracking *tracking)
{
	if (id == ELEM_AMBIENT && !parse_ambient(new_line, scene, tracking))
		return (0);
	else if (id == ELEM_CAMERA && !parse_camera(new_line, scene, tracking))
		return (0);
	else if (id == ELEM_CYLINDER && !parse_cylinder(new_line, scene, tracking))
		return (0);
	else if (id == ELEM_PLANE && !parse_plane(new_line, scene, tracking))
		return (0);
	else if (id == ELEM_SPHERE && !parse_sphere(new_line, scene, tracking))
		return (0);
	else if (id == ELEM_LIGHT && !parse_light(new_line, scene, tracking))
		return (0);
	else if (id == ELEM_UNKNOWN)
		return (print_error("Unknown element identifier"), 0);
	return (1);
}

int	parse_line(char *line, t_scene *scene, t_tracking *tracking)
{
	char	*new_line;
	int		id;
	int		result;

	if (!empty_line(line))
		return (1);
	new_line = trim_whitespace(line);
	if (!new_line)
		return (0);
	id = identify_elem(new_line);
	result = process_element(new_line, id, scene, tracking);
	free(new_line);
	return (result);
}

static int	parse_file_lines(int fd, t_scene *scene, t_tracking *tracking)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!parse_line(line, scene, tracking))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

t_scene	*parse_scene(char *filename)
{
	t_scene		*scene;
	int			fd;
	t_tracking	tracking;

	if (!validate_file(filename))
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Cannot open file"), NULL);
	init_tracking(&tracking);
	scene = init_scene();
	if (!scene)
		return (close(fd), NULL);
	if (!parse_file_lines(fd, scene, &tracking))
	{
		get_next_line(-1);
		return (free_scene(scene), close(fd), NULL);
	}
	get_next_line(-1);
	if (!validate_scene(scene, &tracking))
		return (free_scene(scene), close(fd), NULL);
	close(fd);
	return (scene);
}
