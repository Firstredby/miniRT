/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:25:29 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 10:38:50 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	decimal_place;

	result = 0.0;
	sign = 1.0;
	if (*str == '-' && ++str)
		sign = -1.0;
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
		str++;
	decimal_place = 0.1;
	while (ft_isdigit(*str))
	{
		result += (*str++ - '0') * decimal_place;
		decimal_place *= 0.1;
	}
	return (result * sign);
}
