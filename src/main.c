/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:21:56 by aorth             #+#    #+#             */
/*   Updated: 2025/11/25 12:13:43 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		return (print_error("Usage: ./miniRT <scene_file.rt>\n"), 0);
	scene = parse_scene(argv[1]);
	if (!scene)
		return (0);
	free_scene(scene);
    return (0);
}