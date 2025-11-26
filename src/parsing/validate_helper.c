/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:00:05 by aorth             #+#    #+#             */
/*   Updated: 2025/11/26 11:32:39 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	validate_normalized(t_vec v, char *ele)
{
	double	length;
	double	epsilon;

	epsilon = 0.001;
	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (fabs(length - 1) < epsilon)
		return (1);
	return (file_error("Value must be normalized", ele), 0);
}
