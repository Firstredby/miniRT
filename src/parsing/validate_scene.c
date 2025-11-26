/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:16:01 by aorth             #+#    #+#             */
/*   Updated: 2025/11/26 11:32:18 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	validate_scene(t_scene *scene, t_tracking *tracking)
{
	(void)scene;
	if (!tracking->has_ambient)
		return (print_error("Scene must have one ambient light defined"), \
			0);
	if (!tracking->has_camera)
		return (print_error("Scene must have one camera defined"), 0);
	if (tracking->light_count < 1)
		return (print_error("Scene must have at least one light defined"), \
			0);
	if (tracking->object_cout < 1)
		return (print_error("Scene must have at least one object defined"), \
			0);
	return (1);
}