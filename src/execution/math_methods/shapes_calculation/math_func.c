/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishchyro <ishchyro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:52:58 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/27 12:53:43 by ishchyro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/miniRT.h"

double	discriminant(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	distance(double disc, double a, double b)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(disc)) / (2 * a);
	t2 = (-b + sqrt(disc)) / (2 * a);
	if (t1 > 0)
		return (t1);
	else if (t2 > 0)
		return (t2);
	else
		return (0);
}
